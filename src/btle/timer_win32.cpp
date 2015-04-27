#include <windows.h>

#include "btle/timer.h"
#include "btle/log.h"
#include "btle/verify.h"

using namespace btle;

namespace {
    struct win32_timer_object{
        PHANDLE handle_;
        timercallback* callback_;
        timer* back_pointer_;
    };

    void CALLBACK timer_callback(void* lpParametar,
                            BOOLEAN TimerOrWaitFired)
    {
        win32_timer_object* obj = (win32_timer_object*) lpParametar;
        obj->callback_->timer_expired(obj->back_pointer_);
    }
}

timer::timer()
: object_(NULL)
{
    object_ = new win32_timer_object;
}

timer::~timer()
{
    stop();
    delete ((win32_timer_object*)object_);
}

void timer::start(int ms, timercallback* callback)
{
    stop();
    ((win32_timer_object*)object_)->callback_ = callback;
    ((win32_timer_object*)object_)->back_pointer_ = this;
    CreateTimerQueueTimer(
        ((win32_timer_object*)object_)->handle_,
        NULL,
        timer_callback,
        object_,
        0,
        ms,
        WT_EXECUTEINTIMERTHREAD);
}

void timer::stop()
{
    if( ((win32_timer_object*)object_)->handle_ )
    {
        DeleteTimerQueueTimer(NULL, ((win32_timer_object*)object_)->handle_, NULL);
        CloseHandle (((win32_timer_object*)object_)->handle_);
        ((win32_timer_object*)object_)->handle_ = NULL;
    }
}
