#include <QCoreApplication>
#include "daemon/Core.hh"

int main(int ac, char **av)
{
    QCoreApplication    app(ac, av);
    Core                core;

    core.startDaemon();

    return app.exec();
}
