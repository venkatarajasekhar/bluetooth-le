#ifndef COLLECTORTEST_H
#define COLLECTORTEST_H

#include <QObject>

#include "btle_core.h"
#include "btle/central/collectorqt.h"

class collectortest : public QObject
{
    Q_OBJECT
public:
    explicit collectortest(QObject *parent = 0);
    ~collectortest();

signals:

public slots:

    void slot_device_discovered(device* dev);

public:

    collectorqt* collector_;

};

#endif // COLLECTORTEST_H
