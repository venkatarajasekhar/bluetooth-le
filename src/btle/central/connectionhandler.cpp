
#include <assert.h>
#include "btle/central/connectionhandler.h"
#include "btle/log.h"

using namespace btle::central;

namespace{
    #define Entry    -1
    #define Exit     -2

    enum ch_action
    {
        connect_device_action,
        advertisement_head_received_action,
        disconnect_device_action,
        device_connected_action,
        device_disconnected_action,
        timer_timeout_action
    };
}

connectionhandler::connectionhandler()
: current_(&connectionhandler::free),
  free_(&connectionhandler::free),
  connecting_(&connectionhandler::connecting),
  disconnecting_(&connectionhandler::disconnecting),
  current_device_(NULL),
  reconnectiontryes_(0),
  options_(),
  observers_(),
  timer_(),
  scan_ctrl_(NULL),
  link_ctrl_(NULL),
  devices_(NULL)
{
}

void connectionhandler::setup( device_list* list,
                               connectionhandlerscanctrl* ctrl,
                               connectionhandlerlinkctrl* link_ctrl )
{
    scan_ctrl_ = ctrl;
    link_ctrl_ = link_ctrl;
    devices_ = list;
    current_ = free_;
    current_device_ = NULL;
    timer_.stop();
}

void connectionhandler::advertisement_head_received(device& dev)
{
    if( dev.state() == btle::DEVICE_CONNECTION_PARK )
    {
        (this->*current_)(dev,advertisement_head_received_action);
    }
}

void connectionhandler::connect_device( device& dev )
{
    (this->*current_)(dev,connect_device_action);
}

void connectionhandler::disconnect_device(device& dev )
{
    (this->*current_)(dev,disconnect_device_action);
}

void connectionhandler::device_connected( device& dev )
{
    (this->*current_)(dev,device_connected_action);
}

void connectionhandler::device_disconnected(device& dev )
{
    (this->*current_)(dev,device_disconnected_action);
}

void connectionhandler::set_option(connectionhandler_options option, int value )
{
    options_[option] = value;
}

void connectionhandler::remove_option(connectionhandler_options option)
{
    if( options_.find(option) != options_.end() )
        options_.erase(options_.find(option));
}

void connectionhandler::attach(connectionhandlerobserver* observer)
{
    observers_.push_back(observer);
}

void connectionhandler::detach(connectionhandlerobserver* observer)
{
    for( std::vector<connectionhandlerobserver*>::iterator it = observers_.begin();
         it != observers_.end(); ++it )
    {
        if( (*it) == observer )
        {
            observers_.erase(it);
            return;
        }
    }
}

void connectionhandler::change_device_state(
    device& dev,
    btle::connection_state state )
{
    dev.set_state(state);
    for( std::vector<connectionhandlerobserver*>::iterator it = observers_.begin();
         it != observers_.end(); ++it )
    {
        (*it)->device_state_changed(dev);
    }
}

btle::device* connectionhandler::any_in_state(btle::connection_state state)
{
    for( device_list::const_iterator it = devices_->begin(); it != devices_->end(); ++it )
    {
        if( (*it)->state() == state )
        {
            return (*it);
        }
    }
    return NULL;
}

btle::device* connectionhandler::oldest_in_connection_park()
{
    btle::device* ret (NULL);
    for( device_list::const_iterator it = devices_->begin(); it != devices_->end(); ++it )
    {
        if( (*it)->state() == DEVICE_CONNECTION_PARK )
        {
            if( ret == NULL || (*it)->reconnections_ < ret->reconnections_ )
            {
                ret = (*it);
            }
        }
    }
    return ret;
}

void connectionhandler::free( device& dev, int action )
{
    func_log
    
    switch( action )
    {
        case Entry:
        {
            if( btle::device* it = any_in_state(btle::DEVICE_DISCONNECTION_PARK) )
            {
                change_state(disconnecting_, *it);
            }
            else
            {
                if( options_.find(CONNECTION_DIRECT) != options_.end() )
                {
                    if( btle::device* it = oldest_in_connection_park() )
                    {
                        change_state(connecting_, *it);
                    }
                }
            }
            break;
        }
        case advertisement_head_received_action:
        {
            if( dev.state() == btle::DEVICE_CONNECTION_PARK )
            {
                // change state to connecting
                change_state(connecting_,dev);
            }
            break;
        }
        case connect_device_action:
        {
            switch (dev.state()) {
                case btle::DEVICE_DISCONNECTED:
                {
                    if( options_.find(CONNECTION_DIRECT) == options_.end() )
                    {
                        scan_ctrl_->aquire_start_scan();
                        change_device_state(dev,btle::DEVICE_CONNECTION_PARK);
                    }
                    else
                    {
                        // direct connection
                        change_state(connecting_, dev);
                    }
                    break;
                }
                case btle::DEVICE_DISCONNECTION_PARK:
                {
                    // just change state
                    change_device_state(dev,btle::DEVICE_CONNECTED);
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case disconnect_device_action:
        {
            switch( dev.state() )
            {
                case btle::DEVICE_CONNECTED:
                {
                    change_state(disconnecting_,dev);
                    break;
                }
                case btle::DEVICE_CONNECTION_PARK:
                {
                    change_device_state(dev,btle::DEVICE_DISCONNECTED);
                    break;
                }
                case btle::DEVICE_DISCONNECTED:
                {
                    // just ignore
                    break;
                }
                default:
                {
                    assert(false);
                    break;
                }
            }
            break;
        }
        case device_disconnected_action:
        {
            // unsolicted disconnection
            if( is_reconnection_needed(dev) )
            {
                if( options_.find(CONNECTION_DIRECT) == options_.end() )
                {
                    change_device_state(dev,btle::DEVICE_CONNECTION_PARK);
                }
                else
                {
                    change_state(connecting_, dev);
                }
            }
            else
            {
                change_device_state(dev,btle::DEVICE_DISCONNECTED);
            }
            break;
        }
        case Exit:
        {
            // do nothing
            break;
        }
        default:
        {
            assert(false);
            break;
        }
    }
}

void connectionhandler::connecting( device& dev, int action )
{
    func_log

    switch( action )
    {
        case Entry:
        {
            // stop scan for connection attempt moment
            scan_ctrl_->aquire_stop_scan();
            current_device_ = &dev;
            link_ctrl_->aquire_connect_device(dev);
            change_device_state(dev,btle::DEVICE_CONNECTING);
            if( options_.find(CONNECTION_TIMEOUT) != options_.end() )
            {
                timer_.start(options_.find(CONNECTION_TIMEOUT)->second, this);
            }
            break;
        }
        case device_connected_action:
        {
            assert( current_device_ == &dev );
            change_device_state( dev, btle::DEVICE_CONNECTED );
            // change state to free
            change_state(free_,dev);
            break;
        }
        case device_disconnected_action:
        {
            if( current_device_ == &dev )
            {
                if( is_reconnection_needed(dev) )
                {
                    change_device_state( dev, btle::DEVICE_CONNECTION_PARK );
                    //observer_->scan_devices();
                    change_state(free_,dev);
                }
                else
                {
                    change_device_state( dev, btle::DEVICE_DISCONNECTED );
                    change_state(free_,dev);
                }
            }
            else
            {
                if( is_reconnection_needed(dev) )
                {
                    change_device_state( dev, btle::DEVICE_CONNECTION_PARK );
                    scan_ctrl_->aquire_start_scan();
                }
                else
                {
                    //just propagate state change event
                    change_device_state( dev, btle::DEVICE_DISCONNECTED );
                }
            }
            break;
        }
        case connect_device_action:
        {
            if( current_device_ != &dev )
            {
                switch( dev.state() )
                {
                    case btle::DEVICE_DISCONNECTED:
                    {
                        change_device_state( dev, btle::DEVICE_CONNECTION_PARK );
                        break;
                    }
                    case btle::DEVICE_DISCONNECTION_PARK:
                    {
                        change_device_state( dev, btle::DEVICE_CONNECTED );
                        break;
                    }
                }
            }
            break;
        }
        case advertisement_head_received_action:
        {
            // do nothing
            break;
        }
        case disconnect_device_action:
        {
            if( current_device_ == &dev )
            {
                link_ctrl_->aquire_cancel_pending_connection(dev);
                change_device_state(dev,btle::DEVICE_DISCONNECTED);
                change_state(free_,dev);
            }
            else
            {
                switch( dev.state() )
                {
                    case btle::DEVICE_CONNECTED:
                    {
                        change_device_state(dev,btle::DEVICE_DISCONNECTION_PARK);
                        break;
                    }
                    case btle::DEVICE_CONNECTION_PARK:
                    {
                        change_device_state(dev,btle::DEVICE_DISCONNECTED);
                        break;
                    }
                    default:
                    {
                        assert(false);
                        break;
                    }
                }
            }
            break;
        }
        case timer_timeout_action:
        {
            assert( current_device_ && &dev == current_device_);
            link_ctrl_->aquire_cancel_pending_connection(dev);
            if( is_reconnection_needed(dev) ){
                change_device_state(dev, DEVICE_CONNECTION_PARK);
            }
            // TODO if setting is direct connection
            change_state(free_, dev);
            break;
        }
        case Exit:
        {
            timer_.stop();
            scan_ctrl_->aquire_start_scan();
            break;
        }
        default:
        {
            assert(false);
            break;
        }
    }
}

void connectionhandler::disconnecting(device& dev, int action )
{
    func_log

    switch( action )
    {
        case Entry:
        {
            current_device_ = &dev;
            link_ctrl_->aquire_disconnect_device(dev);
            change_device_state(dev,btle::DEVICE_DISCONNECTING);
            if( options_.find(DISCONNECTION_TIMEOUT) != options_.end() )
            {
                timer_.start(options_.find(DISCONNECTION_TIMEOUT)->second, this);
            }
            break;
        }
        case connect_device_action:
        {
            switch( dev.state() )
            {
                case btle::DEVICE_DISCONNECTION_PARK:
                case btle::DEVICE_DISCONNECTED:
                {
                    change_device_state(dev,btle::DEVICE_CONNECTION_PARK);
                    break;
                }
                case btle::DEVICE_DISCONNECTING:
                {
                    // should current device
                    change_device_state(dev,btle::DEVICE_CONNECTION_PARK);
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case disconnect_device_action:
        {
            switch( dev.state() )
            {
                case btle::DEVICE_CONNECTED:
                {
                    change_device_state(dev,btle::DEVICE_DISCONNECTION_PARK);
                    break;
                }
                case btle::DEVICE_CONNECTION_PARK:
                {
                    change_device_state(dev,btle::DEVICE_DISCONNECTED);
                    break;
                }
                default:
                    assert(false);
            }
            break;
        }
        case device_disconnected_action:
        {
            if( &dev == current_device_ )
            {
                change_device_state(dev,btle::DEVICE_DISCONNECTED);
                change_state(free_,dev);
            }
            else
            {
                if( is_reconnection_needed(dev) )
                {
                    change_device_state(dev,btle::DEVICE_CONNECTION_PARK);
                }
                else
                {
                    change_device_state(dev,btle::DEVICE_DISCONNECTED);
                }
            }
            break;
        }
        case advertisement_head_received_action:
        {
            // do nothing
            break;
        }
        case timer_timeout_action:
        {
            assert( current_device_ && &dev == current_device_);
            change_device_state(dev, DEVICE_DISCONNECTED);
            change_state(free_, dev);
            break;
        }
        case Exit:
        {
            timer_.stop();
            break;
        }
        default:
        {
            assert(false);
            break;
        }
    }
}

void connectionhandler::change_state(kConnectionHndlrState state, device& dev)
{
    (this->*current_)(dev,Exit);
    current_ = state;
    (this->*current_)(dev,Entry);
}

void connectionhandler::timer_expired(timer* t)
{
    (this->*current_)(*current_device_,timer_timeout_action);
}

bool connectionhandler::is_reconnection_needed(device& dev)
{
    if( options_.find(RECONNECTION_TRYES) != options_.end() )
    {
        return ++dev.reconnections_ < options_[RECONNECTION_TRYES];
    }
    return true;
}

