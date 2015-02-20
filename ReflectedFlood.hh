#ifndef REFLECTEDFLOOD_HH
#define REFLECTEDFLOOD_HH

#include "Sniff.hh"

using namespace Tins;

typedef std::pair<IPv4Address, unsigned int>    Spoof;

class ReflectedFlood
{
private:
    IPv4Address                 _target;
    std::vector<Spoof>          _spoofList;

public:
    ReflectedFlood(const std::string &target);

    void        addSpoof(const std::string &spoofedAdress, unsigned int port);
    void        dumpAdress(void);

    void        flood(unsigned int count);
};

#endif // REFLECTEDFLOOD_HH
