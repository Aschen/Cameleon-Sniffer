#ifndef MITM_HH
#define MITM_HH

#include <thread>
#include "Sniff.hh"
#include "AModule.hh"

using namespace Tins;

class Mitm : public AModule
{
private:
    bool                        _run;
    Addresses                   _gateway;
    Addresses                   _victim;

public:
    Mitm(Core &core, std::ostream *out, const std::string &victimIp, const std::string &gatewayIp);
    virtual ~Mitm(void) { }

public:
    void                        poison(void);

    // AModule
public:
    void                        start(void);
    void                        stop(void);
    std::string                 info(void);
    static std::string          help(void);
};

#endif // MITM_HH
