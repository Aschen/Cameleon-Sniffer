#ifndef DNSSPOOF_HH
#define DNSSPOOF_HH

#include <ostream>
#include <fstream>
#include <thread>
#include "Sniff.hh"

using namespace Tins;

class DnsSpoof
{
private:
    NetworkInterface    _iface;
    PacketSender        *_sender;
    Sniffer             *_sniffer;
    std::map<std::string, std::string>  _spoofedHosts;

public:
    DnsSpoof(const std::string &file);

    bool                dumpQuery(PDU &pdu);

    // AModule
public:
    void                start(void);
    void                stop(void);
    static std::string  help(void);


private:
    void                sniff(void);
    void                readHosts(const std::string &file);
};

#endif // DNSSPOOF_HH
