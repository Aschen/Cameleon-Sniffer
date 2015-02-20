#ifndef ADDRESSES_HH
#define ADDRESSES_HH

#include "Sniff.hh"

using namespace Tins;

class Addresses
{
private:
    HWAddress<6>    _mac;
    IPv4Address     _ip;

public:
    Addresses(const HWAddress<6> mac, const IPv4Address ip);

    const HWAddress<6>    mac(void);
    void            mac(const HWAddress<6> newMac);
    const IPv4Address     ip(void);
    void            ip(const IPv4Address newIp);
};

#endif // ADDRESSES_HH
