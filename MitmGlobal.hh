#ifndef MITMGLOBAL_HH
#define MITMGLOBAL_HH

#include <thread>
#include <vector>
#include "Sniff.hh"
#include "AModule.hh"

using namespace Tins;

class MitmGlobal : public AModule
{
private:
    bool                        _run;
    Addresses                   _gateway;
    std::vector<Addresses>      _victims;

public:
    MitmGlobal(Core &core, std::ostream *out, const std::vector<std::string> &victimsIp, const std::string &gatewayIp);
    virtual ~MitmGlobal(void) { }

public:
    void                        poison(void);

    // AModule
public:
    void                        start(void);
    void                        stop(void);
    std::string                 info(void);
    static std::string          help(void);
};

#endif // MITMGLOBAL_HH
