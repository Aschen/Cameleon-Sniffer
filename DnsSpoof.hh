#ifndef DNSSPOOF_HH
#define DNSSPOOF_HH

#include <ostream>
#include <fstream>
#include <thread>
#include "Sniff.hh"
#include "ASniffer.hh"


using namespace Tins;

class DnsSpoof : public ASniffer
{
private:
    const std::string                   _file;
    std::map<std::string, std::string>  _spoofedHosts;

public:
    DnsSpoof(const NetworkInterface &iface, std::ostream *out, const std::string &file);
    ~DnsSpoof(void) { }

    // AModule
public:
    std::string                         info(void) const;
    static std::string                  help(void);

    // ASniffer
public:
    bool                                handler(PDU &pdu);

private:
    void                                readHosts(const std::string &file);
};

#endif // DNSSPOOF_HH
