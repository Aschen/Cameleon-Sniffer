#ifndef DNSSPOOF_HH
#define DNSSPOOF_HH

#include <ostream>
#include <fstream>
#include <thread>
#include "Sniff.hh"
#include "AModule.hh"


using namespace Tins;

class DnsSpoof : public AModule
{
private:
    std::string                         _file;
    Sniffer                             _sniffer;
    std::map<std::string, std::string>  _spoofedHosts;

public:
    DnsSpoof(Core &core, const std::string &file, const std::string &interface);

    bool                spoofQuery(PDU &pdu);

    // AModule
public:
    void                start(void);
    void                stop(void);
    std::string         info(void);
    static std::string  help(void);

private:
    void                sniff(void);
    void                readHosts(const std::string &file);
};

#endif // DNSSPOOF_HH
