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

private:
    const std::string           getDate(void) const;

public:
    static std::string          help(void);

    // ASniffer
private:
    bool                        handler(PDU &pdu);
public:
    std::string                 info(void) const;
};

#endif // DNSDUMP_HH
