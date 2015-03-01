#ifndef CORE_HH
#define CORE_HH

#include <queue>
#include <thread>
#include <mutex>

#include "Sniff.hh"
#include "Addresses.hh"

using namespace Tins;

class Core
{
private:
    NetworkInterface        _iface;
    Addresses               _attacker;
    // Sender
    PacketSender            _sender;
    // Sniffer
    Sniffer                 _sniffer;
    bool                    _senderRun;
    std::thread             _senderThread;
    std::mutex              _senderMutex;
    std::queue<EthernetII>  _pktList;
    std::map<std::string, IPv4Address>  _pingList;

public:
    Core(void);
    Core(const std::string &interface);
    ~Core(void);


public:
    void                    send(const EthernetII &pkt);
    const HWAddress<6>      arpRequest(const IPv4Address &targetIp, const IPv4Address &senderIp, const HWAddress<6> &senderMac);
    const HWAddress<6>      arpRequest(const IPv4Address &targetIp);
    void                    arpReply(const IPv4Address &senderIp, const HWAddress<6> &senderMac, const IPv4Address &targetIp, const HWAddress<6> &targetMac);
    void                    pingHosts(void);

public:
    const HWAddress<6>      mac(void) const;
    const IPv4Address       ip(void) const;
    const NetworkInterface  &interface(void) const;

private:
    void                    startSender(void);
    bool                    pingReply(PDU &pdu);
    void                    sniffPing(void);
};

#endif // CORE_HH
