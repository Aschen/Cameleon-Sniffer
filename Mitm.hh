#ifndef MITM_HH
#define MITM_HH

#include <thread>
#include "Sniff.hh"

using namespace Tins;

class Mitm
{
private:
    NetworkInterface        _iface;
    HWAddress<6>            _attackerMac;
    IPv4Address             _attackerIp;
    bool                    _run;
    PacketSender            *_sender;
    HWAddress<6>            _gatewayMac;
    IPv4Address             _gatewayIp;
    HWAddress<6>            _victimMac;
    IPv4Address             _victimIp;

public:
    Mitm(const std::string &victimIp, const std::string &gatewayIp);
    ~Mitm(void);

    HWAddress<6>            request(IPv4Address &targetIp, IPv4Address &senderIp, HWAddress<6> &senderMac);
    HWAddress<6>            request(IPv4Address &targetIp);
    void                    reply(IPv4Address &senderIp, HWAddress<6> &senderMac, IPv4Address &targetIp, HWAddress<6> &targetMac);

    void                    start(void);
    void                    stop(void);

private:
    void                    poison(void);
    void                    restore(void);
};

#endif // MITM_HH
