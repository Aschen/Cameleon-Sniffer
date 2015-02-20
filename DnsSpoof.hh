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

    void                start(void);
    void                stop(void);
    bool                dumpQuery(PDU &pdu);

private:
    void                sniff(void);
    void                readHosts(const std::string &file);
};

#endif // DNSSPOOF_HH
