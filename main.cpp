#include "Mitm.hh"
#include "Core.hh"
#include "DnsSpoof.hh"
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
    std::string tot;
//    Core    core;
//    Mitm    mitm(core, av[1], "192.168.1.1");

//    std::thread   t(&Mitm::start, mitm);
//    t.detach();


//    std::cin >> tot;

//    mitm.stop();
    Prompt  pr;
    DnsSpoof    dnsSpoof("hosts.txt");

    dnsSpoof.start();
    pr.launch();
    dnsSpoof.stop();
}
