#ifndef ASNIFFER_HH
#define ASNIFFER_HH

#include <tins/tins.h>
#include <thread>
#include "IModule.hh"

using namespace Tins;

class ASniffer : public IModule
{
    // Private ?
protected:
    Sniffer                         _sniffer;
    NetworkInterface                _iface;
    const std::string               _name;
    std::ostream                    *_out;

public:
    ASniffer(const NetworkInterface &iface, const std::string &name, const std::string &filter, std::ostream *out);
    virtual ~ASniffer(void) { }

    // Private ?
private:
    void                            sniff(void);

protected:
    virtual bool                    handler(PDU &pdu) = 0;

    // IModule
public:
    void                            start(void);
    void                            stop(void);
    virtual std::string             info(void) const = 0;
    virtual const std::string       &name(void) const;
};

#endif // ASNIFFER_HH
