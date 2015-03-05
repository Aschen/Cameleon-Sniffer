#include "SurfWatcher.hh"

SurfWatcher::SurfWatcher(const NetworkInterface &interface, std::ostream *out, const std::string &filename, IPv4Address ip)
    : ASniffer(interface, "SurfWatcher", "tcp and dst port 80", out), _filename(filename), _type(SurfWatcher::IP), _hostname(""), _ip(ip)
{
}

SurfWatcher::SurfWatcher(const NetworkInterface &interface, std::ostream *out, const std::string &filename, std::string &hostname)
    : ASniffer(interface, "SurfWatcher", "tcp and dst port 80", out), _filename(filename), _type(SurfWatcher::HOST), _hostname(hostname)
{
}

SurfWatcher::SurfWatcher(const NetworkInterface &interface, std::ostream *out, const std::string &filename)
    : ASniffer(interface, "SurfWatcher", "tcp and dst port 80", out), _filename(filename), _type(SurfWatcher::ALL)
{
}

bool SurfWatcher::handler(PDU &pdu)
{
    // EthernetII / IP / TCP
    EthernetII eth = pdu.rfind_pdu<EthernetII>();
    Tins::IP ip = eth.rfind_pdu<Tins::IP>();
    TCP tcp = ip.rfind_pdu<TCP>();

    Tins::RawPDU::payload_type payload = tcp.rfind_pdu<RawPDU>().payload();
    std::stringstream       ss;

    for (u_int8_t data : payload)
        ss << data;

    HTTP        http(ss);

    if (_type == SurfWatcher::ALL)
        watchAll(http, ip.src_addr());
    else if (_type == SurfWatcher::IP)
        watchIp(http, ip.src_addr());
    else
        watchHost(http, ip.src_addr());

    return true;
}

void SurfWatcher::watchAll(const HTTP &http, Tins::IP::address_type ip) const
{
    std::string         location;

    try
    {
        isRessource(http.location());
        location = http.getHeader("Host") + http.location();
        *_out << ip << " --> " << location << std::endl;
    }
    catch (std::out_of_range &e) { }
}

void SurfWatcher::watchIp(const HTTP &http, Tins::IP::address_type ip) const
{
    std::string         location;

    try
    {
        if (ip == _ip)
        {
            isRessource(http.location());
            location = http.getHeader("Host") + http.location();
            *_out << ip << " --> " << location << std::endl;
        }
    }
    catch (std::out_of_range &e) { }
}

void SurfWatcher::watchHost(const HTTP &http, Tins::IP::address_type ip) const
{
    std::string         location;

    try
    {
        if (_hostname == http.getHeader("Host"))
        {
            isRessource(http.location());
            location = _hostname + http.location();
            *_out << ip << " --> " << location << std::endl;
        }
    }
    catch (std::out_of_range &e) { }
}

void SurfWatcher::isRessource(const std::string &location) const
{
    for (int i = 0; _extensions[i]; i++)
    {
        if (!(location.find(_extensions[i]) == location.npos))
            throw std::out_of_range("This is a ressource");
    }
}

std::string SurfWatcher::help(void) { return std::string("Start SurfWatcher.\n") + "\tOptions : <all | ip | host> <filename> [ip | hostname]"; }

std::string SurfWatcher::info(void) const
{
    std::string     msg;

    if (_type == SurfWatcher::ALL)
        msg += "Ip = *, Host = *";
    else if (_type == SurfWatcher::HOST)
        msg += "Host = " + _hostname;
    else
        msg += "Ip = " + _ip;
    return msg + ", File = " + _filename;
}
