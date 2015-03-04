#ifndef ASENDER_HH
#define ASENDER_HH

#include <tins/packet_sender.h>
#include "Sniff.hh"
#include "IModule.hh"

using namespace Tins;

class ASender : public IModule
{
protected:
    NetworkInterface            _iface;
    const std::string           _name;
    std::ostream                *_out;
    PacketSender                _sender;

public:
    ASender(const NetworkInterface &iface, const std::string &name, std::ostream *out);
    virtual ~ASender(void) { }

    // IModule
public:
    virtual void                start(void) = 0;
    virtual void                stop(void) = 0;
    virtual std::string         info(void) const = 0;
    virtual const std::string   &name(void) const;
};

#endif // ASENDER_HH
