#ifndef DNSDUMP_HH
#define DNSDUMP_HH

#include <time.h>

#include "Sniff.hh"
#include "ASniffer.hh"

class DnsDump : public ASniffer
{
private:
    const std::string           _filename;

public:
    DnsDump(const NetworkInterface &iface, std::ostream *out, const std::string &filename);
    ~DnsDump(void);

    // AModule
public:
    std::string                 info(void) const;
    static std::string          help(void);

    // ASniffer
protected:
    bool                        handler(PDU &pdu);
};

#endif // DNSDUMP_HH
