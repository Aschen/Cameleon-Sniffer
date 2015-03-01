#ifndef TCPKILL_HH
#define TCPKILL_HH

#include "ASniffer.hh"

using namespace Tins;

class TcpKill : public ASniffer
{
private:
    const IPv4Address               _dstIp;
    const IPv4Address               _srcIp;
    const int                       _port;

public:
    TcpKill(Core &core, std::ostream *out, std::string &dstIp, std::string &srcIp, std::string &port);
    ~TcpKill(void) { }

    // AModule
public:
    virtual std::string             info(void);
    static std::string              help(void);

    // ASniffer
public:
    bool                            handler(PDU &pdu);
};

#endif // TCPKILL_HH
