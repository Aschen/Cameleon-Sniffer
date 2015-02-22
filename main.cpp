#include "Mitm.hh"
#include "Core.hh"
#include "DnsSpoof.hh"
#include "DnsDump.hh"
#include "Prompt.hh"

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
    std::string tot;
    Core    core;
    DnsDump dump(core);

    dump.start();
    std::cin >> tot;

    dump.stop();
//    Prompt  pr;

//    pr.launch();
    return 0;
}
