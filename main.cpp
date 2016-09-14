#include <QCoreApplication>
#include "daemon/Core.hh"
#include "modules/Dummy.hh"
#include "modules/ModuleFactory.hpp"

int main(int ac, char **av)
{
    QCoreApplication    app(ac, av);
    Core    core;
    QStringList args;

    args << "DnsWatcher";
    args << "spy";
    args << "dns_out.txt";

    core.addModule(ModuleFactory::create(args));

    QStringList args2;

    args2 << "DnsWatcher";
    args2 << "spy2";
    args2 << "dns_out2.txt";

    core.addModule(ModuleFactory::create(args2));

    return app.exec();
}
