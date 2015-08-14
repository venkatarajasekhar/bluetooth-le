
#include "btle/timer.h"
#include "btle/log.h"
#include "btle/verify.h"

#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>

#define CLOCKID CLOCK_REALTIME
#define SIG SIGUSR1
//timer_t timerid;

using namespace btle;

namespace {
    void routine (int sig)
    {
    }

    struct timer_objects{
        struct sigaction sa;
        struct itimerval timer;
    };
}

timer::timer()
: object_(new timer_objects)
{
}

timer::~timer()
{
    stop();
    delete object_;
}

void timer::start(int ms, timercallback* callback)
{
    struct sigaction& sa = ((timer_objects*)object_)->sa;
    struct itimerval& timer = ((timer_objects*)object_)->timer;

    memset (&sa, 0, sizeof (sa));
    sa.sa_handler = &routine;
    sigaction (SIGVTALRM, &sa, NULL);
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = ms*1000;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    setitimer (ITIMER_VIRTUAL, &timer, NULL);
}

void timer::stop()
{
    //TODO
}
