#include "Mitm.hh"
#include "DnsSpoof.hh"
#include "Core.hh"

using namespace Tins;

void    toto(void)
{
    for (int i = 0; i < 5; i++)
    {
        std::cout << "hello" << std::endl;
        sleep(1);
    }
}

int main(int ac, char *av[])
{
    (void)ac;
    (void)av;
    std::string tot;


//    Mitm        mitm(av[1], "192.168.1.254");
//    DnsSpoof    spoof("hosts.txt");

//    mitm.start();
//    spoof.start();
    NetworkInterface::Info  info = NetworkInterface("wlan0").addresses();
    Addresses    me(info.hw_addr, info.ip_addr);

    std::cout << me.ip() << " " << me.mac() << std::endl;
//    core.stop();
//    spoof.stop();
//    mitm.stop();
}
