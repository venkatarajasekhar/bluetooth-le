
#include "btle/central/linux/bluezperipheraldevice.h"

using namespace btle;
using namespace btle::central;
using namespace btle::central::linux_platform;

bluezperipheraldevice::bluezperipheraldevice(const bda &addr)
: device(addr)
{
}

void bluezperipheraldevice::push(messagebase* message)
{
    q_mutex_.lock();
    queue_.push_back(message);
    q_mutex_.unlock();
}

void bluezperipheraldevice::message_thread()
{
    do{
        q_mutex_.lock();
        messagebase* msg = queue_.front();
        queue_.pop_front();
        q_mutex_.unlock();
        msg->process(this);
    }while(true);
}
