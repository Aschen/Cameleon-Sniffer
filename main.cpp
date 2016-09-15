#include <QCoreApplication>
#include "daemon/Core.hh"
#include "modules/ModuleFactory.hpp"

int main(int ac, char **av)
{
    QCoreApplication    app(ac, av);
    Core    core;

    core.addModule(ModuleFactory::create({"DnsWatcher", "spy", "dns_out.txt"}));

    core.addModule(ModuleFactory::create({"DnsWatcher", "spy2", "dns_out2.txt"}));

    core.removeModule("spy");

    return app.exec();
}
