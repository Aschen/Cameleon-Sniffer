#include "Addresses.hh"

Addresses::Addresses(const HWAddress<6> mac, const IPv4Address ip) : _mac(mac), _ip(ip) {}

const HWAddress<6> Addresses::mac(void) { return _mac; }
void Addresses::mac(const HWAddress<6> newMac) { _mac = newMac; }

const IPv4Address Addresses::ip(void) { return _ip; }
void Addresses::ip(const IPv4Address newIp) { _ip = newIp; }
