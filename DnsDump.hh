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
    DnsDump(Core &core, std::ostream *out, std::string &filename);
    ~DnsDump(void);

    const std::string           getDate(void);

    // AModule
public:
    std::string                 info(void);
    static std::string          help(void);

    // ASniffer
protected:
    bool                        handler(PDU &pdu);

};

#endif // DNSDUMP_HH
