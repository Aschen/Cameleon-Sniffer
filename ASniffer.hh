#ifndef ASNIFFER_HH
#define ASNIFFER_HH

#include <thread>

#include "Sniff.hh"
#include "AModule.hh"

using namespace Tins;

class ASniffer : public AModule
{
protected:
    Sniffer                         _sniffer;

public:
    ASniffer(const NetworkInterface &iface, const std::string &name, const std::string &filter, std::ostream *out);
    virtual ~ASniffer(void) { }

    // Private ?
protected:
    void                            sniff(void);

protected:
    virtual bool                    handler(PDU &pdu) = 0;

    // AModule
public:
    void                            start(void);
    void                            stop(void);
    virtual std::string             info(void) const = 0;
};

#endif // ASNIFFER_HH
