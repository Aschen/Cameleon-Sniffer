#include "Core.hh"

/* CONSTRUCTORS / DESTRUCTORS */
Core::Core(void)
    : _iface(NetworkInterface::default_interface()), _attacker(_iface.addresses().hw_addr, _iface.addresses().ip_addr), _sender(_iface), _sniffer(_iface.name(), Sniffer::PROMISC), _senderRun(true)
{
     _senderThread = std::thread(&Core::startSender, this);
     _senderThread.detach();
}

Core::Core(const std::string &interface)
    : _iface(NetworkInterface(interface)), _attacker(_iface.addresses().hw_addr, _iface.addresses().ip_addr), _sender(_iface), _sniffer(_iface.name(), Sniffer::PROMISC), _senderRun(true)
{
    _senderThread = std::thread(&Core::startSender, this);
    _senderThread.detach();
}

Core::~Core(void)
{
    _senderMutex.unlock();
    _senderRun = false;
}


/* GETTERS / SETTERS */
const HWAddress<6> Core::mac(void) const { return _attacker.mac(); }

const IPv4Address Core::ip(void) const { return _attacker.ip(); }

const NetworkInterface  &Core::interface(void) const { return _iface; }


/* PUBLIC MEMBERS */
const HWAddress<6> Core::arpRequest(const IPv4Address &targetIp, const IPv4Address &senderIp, const HWAddress<6> &senderMac)
{
    EthernetII      arpReq = ARP::make_arp_request(targetIp, senderIp, senderMac);
    PDU             *response;

    // Add arp request to send queue ? How to send_recv ?
    // The request is not for us
    if (senderIp != _attacker.ip() && senderMac != _attacker.mac())
        send(arpReq);
    else if ((response = _sender.send_recv(arpReq, _iface)))
        return response->rfind_pdu<ARP>().sender_hw_addr();

    // Better to throw exception
    return HWAddress<6>("00:00:00:00:00:00");
}

// Resolve for me
const HWAddress<6> Core::arpRequest(const IPv4Address &targetIp)
{
    return arpRequest(targetIp, _attacker.ip() , _attacker.mac());
}

/* Tell (targetIp/targetMac) that senderIp is on senderMac
 * Usually senderIp is the gateway, senderMac is the attacker and target is the victim
 */
void Core::arpReply(const IPv4Address &senderIp, const HWAddress<6> &senderMac, const IPv4Address &targetIp, const HWAddress<6> &targetMac)
{
    EthernetII      rep = ARP::make_arp_reply(targetIp, senderIp, targetMac, senderMac);

    send(rep);
}

void Core::pingHosts(void)
{
    // Start range at 192.168.1.1
    IPv4Range      range = IPv4Range::from_mask( _iface.addresses().ip_addr, _iface.addresses().netmask);

    _sniffer.set_filter("");
    std::thread t(&Core::sniffPing, this);
    t.detach();

    int i = 0;
    for (IPv4Range::const_iterator it = range.begin(); it != range.end(); ++it)
    {
        if (i > 150)
        {
            IP  ip = IP(*it, _iface.addresses().ip_addr);
            ICMP icmp = ICMP(ICMP::ECHO_REQUEST);
            RawPDU payload = RawPDU("0123456789101234567890123456789012345678901234567");

            ip / icmp / payload;
            std::cout << "Send request to " << *it << std::endl;
            _sender.send(ip);
        }
        i++;
    }
}

bool Core::pingReply(PDU &pdu)
{
    // EthernetII / IP / UDP / RawPDU
    EthernetII eth = pdu.rfind_pdu<EthernetII>();
    IP ip = eth.rfind_pdu<IP>();
    ICMP icmp = ip.rfind_pdu<ICMP>();

    if (icmp.type() == ICMP::ECHO_REPLY)
    {
        std::map<std::string, IPv4Address>::iterator it = _pingList.find(ip.src_addr().to_string());

        if (it == _pingList.end())
        {
            std::cout << "Found host " << ip.src_addr() << " up " << std::endl;
            _pingList[ip.src_addr().to_string()] = ip.src_addr();
        }
    }
    return true;
}

void Core::sniffPing(void)
{
    _sniffer.sniff_loop(make_sniffer_handler(this, &Core::pingReply));
}

void Core::send(const EthernetII &pkt)
{
    _pktList.push(pkt);

    // Make sure to not unlock a not locked mutex
    if (_senderMutex.try_lock())
        _senderMutex.unlock();
    else
        _senderMutex.unlock();
}

/* PRIVATE MEMBERS */
void Core::startSender(void)
{
    while (_senderRun)
    {
        // Wait available packets
        _senderMutex.lock();
        while (!_pktList.empty())
        {
            _sender.send(_pktList.front(), _iface);
            _pktList.pop();
        }
    }
}
