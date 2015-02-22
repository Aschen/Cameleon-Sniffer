#ifndef ASNIFFER_HH
#define ASNIFFER_HH

#include "Sniff.hh"
#include "AModule.hh"

using namespace Tins;

class ASniffer : public AModule
{
protected:
    Sniffer                         _sniffer;

public:
    ASniffer(Core &core, const std::string &name, const std::string &filter);
    virtual ~ASniffer(void) { }

    // AModule
public:
    virtual void                    start(void) = 0;
    virtual void                    stop(void) = 0;
    virtual std::string             info(void) = 0;
};

#endif // ASNIFFER_HH
