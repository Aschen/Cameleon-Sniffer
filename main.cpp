#include <QCoreApplication>
#include "daemon/Core.hh"
#include <tins/network_interface.h>

int main(int ac, char **av)
{
    QCoreApplication    app(ac, av);
    Core                core;
    Tins::NetworkInterface      iface = Tins::NetworkInterface::default_interface();

    if (ac == 2)
    {
        iface = Tins::NetworkInterface(av[1]);
    }
    core.iface(QString::fromStdString(iface.name()));

    core.startDaemon();

    return app.exec();
}
