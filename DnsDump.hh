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
    void                        start(void);
    void                        stop(void);
    std::string                 info(void);

private:
    bool                        dumpQuery(PDU &pdu);
    void                        sniff(void);
};

#endif // DNSDUMP_HH
