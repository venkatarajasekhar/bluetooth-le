
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
    std::unique_lock<std::mutex> lock(q_mutex_);
    queue_.push_back(message);
    q_condition_.notify_all();
}

void bluezperipheraldevice::message_thread()
{
    do{
        messagebase* msg(NULL);
        {
            std::unique_lock<std::mutex> lock(q_mutex_);
            q_condition_.wait(lock);
            queue_.front();
            queue_.pop_front();
        }
        msg->process(this);
    }while(true);
}
