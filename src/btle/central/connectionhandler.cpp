
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
: current_state_(&connectionhandler::free),
  free_state_(&connectionhandler::free),
  connecting_state_(&connectionhandler::connecting),
  disconnecting_state_(&connectionhandler::disconnecting)
{
}

void connectionhandler::advertisement_head_received(device& dev)
{
    if( dev.state() == btle::DEVICE_CONNECTION_PARK )
    {
        (this->*current_state_)(dev,advertisement_head_received_action);
    }
}

void connectionhandler::connect_device( device& dev )
{
    (this->*current_state_)(dev,connect_device_action);
}

void connectionhandler::disconnect_device(device& dev )
{
    (this->*current_state_)(dev,disconnect_device_action);
}

void connectionhandler::device_connected( device& dev )
{
    (this->*current_state_)(dev,device_connected_action);
}

void connectionhandler::device_disconnected(device& dev )
{
    (this->*current_state_)(dev,device_disconnected_action);
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

            }
            break;
        }
        case advertisement_head_received_action:
        {
            if( dev.state() == btle::DEVICE_CONNECTION_PARK )
            {
            }
            break;
        }
        case disconnect_device_action:
        {
            switch( dev.state() )
            {
                case btle::DEVICE_CONNECTED:
                {
                    break;
                }
                case btle::DEVICE_CONNECTION_PARK:
                {
                    break;
                }
                case btle::DEVICE_DISCONNECTED:
                {
                    // just ignore if allready disconnected
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
            break;
        }
        case device_connected_action:
        {
            break;
        }
        case device_disconnected_action:
        {
            if( current_device_ == &dev )
            {

            }
            else
            {

            }
            break;
        }
        case connect_device_action:
        {

            break;
        }
        case advertisement_head_received_action:
        {
            // do nothing
            break;
        }
        case disconnect_device_action:
        {
            switch( dev.state() )
            {
                case btle::DEVICE_CONNECTED:
                {
                    break;
                }
                case btle::DEVICE_CONNECTING:
                {
                    break;
                }
                case btle::DEVICE_CONNECTION_PARK:
                {
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
            break;
        }
        case connect_device_action:
        {
            break;
        }
        case disconnect_device_action:
        {
            switch( dev.state() )
            {
                case btle::DEVICE_CONNECTED:
                {
                    break;
                }
                case btle::DEVICE_CONNECTION_PARK:
                {
                    break;
                }
                case btle::DEVICE_DISCONNECTED:
                {
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
            if( &dev == current_device_ )
            {
            }
            else
            {
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
    (this->*current_state_)(dev,Exit);
    current_state_ = state;
    (this->*current_state_)(dev,Entry);
}
