#include "Daemon.hh"

int main(int ac, char **av)
{    
    if (ac < 2)
    {
        std::cout << "Usage : " << av[0] << " <socket>" << std::endl;
        return 1;
    }

    if (getuid() != 0)
    {
        std::cout << "Must be root." << std::endl;
        return 1;
    }

    try
    {
        Daemon      d(av[1]);

        d.start();
    }
    catch (std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
