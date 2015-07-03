#include <QCoreApplication>
#include "collectortest.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    collectortest test;

    const std::vector<std::string>& plugins = test.collector_->plugins_available();

    for( std::vector<std::string>::const_iterator it = plugins.begin();  it != plugins.end(); ++it )
    {
        _log("plugin name: %s", it->c_str());
    }

    if( !test.collector_->auto_start() )
    {
        test.collector_->start_scan();

    }

    return a.exec();
}
