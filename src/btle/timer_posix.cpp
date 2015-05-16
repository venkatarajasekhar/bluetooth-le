
#include "btle/timer.h"
#include "btle/log.h"
#include "btle/verify.h"

using namespace btle;

namespace {

}

timer::timer()
: object_(NULL)
{
}

timer::~timer()
{
    stop();
}

void timer::start(int ms, timercallback* callback)
{

}

void timer::stop()
{

}
