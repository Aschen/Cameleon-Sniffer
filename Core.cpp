#include "Core.hh"

/* CONSTRUCTORS / DESTRUCTORS */
Core::Core(void)
    : _iface(NetworkInterface::default_interface()), _attacker(_iface.addresses().hw_addr, _iface.addresses().ip_addr), _sender(_iface), _senderRun(true)
{
     _senderThread = std::thread(&Core::startSender, this);
     _senderThread.detach();
}

Core::Core(const std::string &interface)
    : _iface(NetworkInterface(interface)), _attacker(_iface.addresses().hw_addr, _iface.addresses().ip_addr), _sender(_iface), _senderRun(true)
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
    _sender.open_l2_socket(_iface);
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
