#include "Daemon.hh"

int main(void)
{
    if (getuid() != 0)
    {
        std::cout << "Must be root." << std::endl;
        return 1;
    }

    try
    {
        Daemon      d("/etc/cameleon/cameleon.sock", "eth0");

        d.start();
    }
    catch (std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
