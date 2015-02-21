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
//    DnsSpoof    dnsSpoof("hosts.txt");

//    std::thread   t(&Mitm::start, mitm);
//    t.detach();

//    dnsSpoof.start();

//    std::cin >> tot;

//    dnsSpoof.stop();
//    mitm.stop();
    Prompt  pr;
    std::cout << "ARP SPOOFING DOESNT STOP CORRECTLY !!" << std::endl;

    pr.launch();
}
