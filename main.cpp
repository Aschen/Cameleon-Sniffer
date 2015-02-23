#include "Mitm.hh"
#include "Core.hh"
#include "DnsSpoof.hh"
#include "DnsDump.hh"
#include "Prompt.hh"
#include "Daemon.hh"

using namespace Tins;

void    toto(void)
{
    for (int i = 0; i < 5; i++)
    {
        std::cout << "hello" << std::endl;
        sleep(1);
    }
}

int main(int ac, char **av)
{    
    (void)ac;
    (void)av;
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
