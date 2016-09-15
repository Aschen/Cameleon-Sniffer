#ifndef Mitm_HH
#define Mitm_HH

#include <vector>
#include <thread>
#include <unistd.h>
#include "Addresses.hh"
#include "ASender.hh"

using namespace Tins;

class Mitm : public ASender
{
private:
    bool                        _run;
    Addresses                   _attacker;
    Addresses                   _gateway;
    std::vector<IPv4Address>    _victims;
    std::vector<EthernetII>     _poisonPackets;
    std::vector<EthernetII>     _basePackets;

public:
    Mitm(const NetworkInterface &iface, std::ostream *out,
      const std::vector<std::string> &victimsIp,
      const std::string &gatewayIp);
    virtual ~Mitm(void) { }

public:
    void                        poison(void);
    static std::string          help(void);


    // ASender
public:
    void                        start(void);
    void                        stop(void);
    std::string                 info(void) const;

private:
    const HWAddress<6>          arpRequest(const IPv4Address &targetIp);
    void                        arpReply(const IPv4Address &senderIp, const HWAddress<6> &senderMac, const IPv4Address &targetIp, const HWAddress<6> &targetMac);
};

#endif // Mitm_HH
