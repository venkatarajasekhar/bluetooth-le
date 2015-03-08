
#include <assert.h>
#include "btle/central/connectionhandler.h"

using namespace btle::central;

namespace{
    #define Entry    -1
    #define Exit     -2

    enum handler_action
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
  disconnecting_(&connectionhandler::disconnecting)
{
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

void connectionhandler::change_device_state(
    device& dev,
    btle::connection_state state )
{
    dev.set_state(state);
    observer_->device_state_updated(dev);
}

void connectionhandler::free( device& dev, int action )
{
    switch( action )
    {
        case Entry:
        {

            break;
        }
        case connect_device_action:
        {
            if( dev.state() == btle::DEVICE_DISCONNECTED )
            {
                change_device_state(dev,btle::DEVICE_CONNECTION_PARK);
                observer_->scan_devices();
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
                change_device_state(dev,btle::DEVICE_CONNECTION_PARK);
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
    switch( action )
    {
        case Entry:
        {
            current_device_ = &dev;
            central_->connect_device(dev);
            change_device_state(dev,btle::DEVICE_CONNECTING);
            // TODO start timer
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
                    observer_->scan_devices();
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
                    observer_->scan_devices();
                }
                else
                {
                    //just propagate state change event
                    change_device_state( dev, btle::DEVICE_DISCONNECTED );
                    // dev.reset();
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
                central_->cancel_pending_connection(dev);
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
            //
            assert( current_device_ != NULL );

            break;
        }
        case Exit:
        {
            //stop_timer();
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
    switch( action )
    {
        case Entry:
        {
            current_device_ = &dev;
            central_->disconnect_device(dev);
            change_device_state(dev,btle::DEVICE_DISCONNECTING);
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
                // unsolicted disconnection to some other device
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
            assert( current_device_ != NULL );
            break;
        }
        case Exit:
        {
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

bool connectionhandler::is_reconnection_needed(device& dev)
{
    return ++dev.reconnections_ < reconnectiontryes_;
}

