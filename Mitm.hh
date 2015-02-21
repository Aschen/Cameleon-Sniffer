#ifndef MITM_HH
#define MITM_HH

#include <thread>
#include "Sniff.hh"
#include "AModule.hh"

using namespace Tins;

class Mitm : public AModule
{
private:
    bool                    _run;
    Addresses               _gateway;
    Addresses               _victim;

public:
    Mitm(Core &core, const std::string &victimIp, const std::string &gatewayIp);
    virtual ~Mitm(void) { }

    // AModule
public:
    void                    start(void);
    void                    stop(void);
};

#endif // MITM_HH
