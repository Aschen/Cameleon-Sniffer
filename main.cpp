#include <QCoreApplication>
#include "daemon/Core.hh"
#include "modules/Dummy.hh"

int main(int ac, char **av)
{
    QCoreApplication    app(ac, av);
    Core    core;

    core.addModule(new Dummy("toto"));
    core.addModule(new Dummy("tata"));
    core.addModule(new Dummy("titi"));
    core.addModule(new Dummy("tutu"));

    return app.exec();
}
