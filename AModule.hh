#ifndef AMODULE_HH
#define AMODULE_HH

#include <tins/packet_sender.h>
#include "Sniff.hh"

using namespace Tins;

class AModule
{
protected:
    NetworkInterface            _iface;
    const std::string           _name;
    std::ostream                *_out;
    PacketSender                _sender;

public:
    AModule(const NetworkInterface &iface, const std::string &name, std::ostream *out);
    virtual ~AModule(void) { }

public:
    const std::string           &name(void) const;

public:
    virtual void                start(void) = 0;
    virtual void                stop(void) = 0;
    virtual std::string         info(void) const = 0;

protected:
    const std::string           getDate(void) const;
};

#endif // AMODULE_HH
