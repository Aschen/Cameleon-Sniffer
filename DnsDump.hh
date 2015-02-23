#ifndef DNSDUMP_HH
#define DNSDUMP_HH

#include "Sniff.hh"
#include "ASniffer.hh"

class DnsDump : public ASniffer
{
public:
    DnsDump(Core &core);

    // AModule
public:
    std::string                 info(void);

    // ASniffer
protected:
    bool                        handler(PDU &pdu);

};

#endif // DNSDUMP_HH
