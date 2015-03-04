#ifndef DNSSPOOF_HH
#define DNSSPOOF_HH

#include "ASniffer.hh"

using namespace Tins;

class DnsSpoof : public ASniffer
{
private:
    const std::string                   _filename;
    PacketSender                        _sender;
    std::map<std::string, std::string>  _spoofedHosts;

public:
    DnsSpoof(const NetworkInterface &iface, std::ostream *out, const std::string &file);
    ~DnsSpoof(void) { }

private:
    void                                readHosts(const std::string &file);

public:
    static std::string                  help(void);


    // ASniffer
private:
    bool                                handler(PDU &pdu);
public:
    std::string                         info(void) const;
};

#endif // DNSSPOOF_HH
