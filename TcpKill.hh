#ifndef TCPKILL_HH
#define TCPKILL_HH

#include "ASniffer.hh"

using namespace Tins;

class TcpKill : public ASniffer
{
public:
    typedef enum e_type
    {
        ServerToVictim = 1,
        AllToServer,
        VictimToAll
    } TYPE;

private:
    const IPv4Address               _dstIp;
    const IPv4Address               _srcIp;
    const int                       _port;
    const TYPE                      _type;

public:
    // Kill traffic from dstIp:port to srcIp
    TcpKill(Core &core, std::ostream *out, std::string &dstIp, std::string &srcIp, std::string &port);
    // Kill all traffic from port to srcIP
    TcpKill(Core &core, std::ostream *out, std::string &srcIp, std::string &port, bool flag);
    // Kill all traffic from dstIp:port
    TcpKill(Core &core, std::ostream *out, std::string &dstIp, std::string &port);

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
