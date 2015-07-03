#include "collectortest.h"

collectortest::collectortest(QObject *parent) : QObject(parent)
{
    collector_ = new collectorqt(this);
    connect(collector_,SIGNAL(signal_device_discovered(device*)),this,
            SLOT(slot_device_discovered(device*)));
}

collectortest::~collectortest()
{

}

void collectortest::slot_device_discovered(device* dev)
{
    _log("device discovered name: %s",dev->name().c_str());
}
