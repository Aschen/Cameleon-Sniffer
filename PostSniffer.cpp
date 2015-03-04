#include "PostSniffer.hh"

PostSniffer::PostSniffer(const NetworkInterface &interface, std::ostream *out, const std::string &filename, const std::vector<std::string> &keys)
    : ASniffer(interface, "PostSniffer", "tcp and dst port 80", out), _filename(filename), _hostname("All"), _type(PostSniffer::KEYS), _keys(keys)
{
}

PostSniffer::PostSniffer(const NetworkInterface &interface, std::ostream *out, const std::string &filename, const std::string &hostname)
    : ASniffer(interface, "PostSniffer", "tcp and dst port 80", out), _filename(filename), _hostname(hostname), _type(PostSniffer::HOSTNAME)
{
}

PostSniffer::PostSniffer(const NetworkInterface &interface, std::ostream *out, const std::string &filename)
    : ASniffer(interface, "PostSniffer", "tcp and dst port 80", out), _filename(filename), _hostname("All"), _type(PostSniffer::ALL)
{
}

std::string PostSniffer::info(void) const
{
    std::string     msg;
    std::string     keys;

    if (_type == PostSniffer::KEYS)
    {
        msg += "Keys = ";
        for (std::string key : _keys)
            msg += key + " ";
    }
    else if (_type == PostSniffer::HOSTNAME)
        msg += "Hostname = " + _hostname;
    else if (_type == PostSniffer::ALL)
        msg += "Hostname = ALL";

    return msg + ", File = " + _filename;
}

std::string PostSniffer::help(void) { return std::string("Start PostSniffer.\n") + "\tOptions : <all | keys | host> <filename> [keys | hostname]"; }

bool PostSniffer::handler(PDU &pdu)
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

    if (http.verb() == "POST")
    {        
        if (_type == PostSniffer::KEYS)
            sniffKeys(http, ip.src_addr());
        else if (_type == PostSniffer::HOSTNAME)
            sniffHostname(http, ip.src_addr());
        else if (_type == PostSniffer::ALL)
            sniffAll(http, ip.src_addr());
    }
    return true;
}

void PostSniffer::sniffKeys(const HTTP &http, Tins::IP::address_type ip)
{
    std::string     value;

    try
    {
        for (std::string key : _keys)
        {
            value = http.getValue(key);
            *_out << http.getHeader("Host") << " from " << ip << "\t" << key << " = " << value << std::endl;
        }
        *_out << std::endl;
    }
    catch (std::out_of_range &e)
    {
        // Key not present
    }
}

void PostSniffer::sniffHostname(const HTTP &http, Tins::IP::address_type ip)
{
    try
    {
        if (_hostname == http.getHeader("Host"))
        {
            *_out << _hostname << " from " << ip << std::endl;
            // Dump all post data
            for (std::pair<std::string, std::string> data : http.data())
            {
                *_out << "\t" << data.first << " = " << data.second << std::endl;
            }
            *_out << std::endl;
        }
    }
    catch (std::out_of_range &e)
    {
    }
}

void PostSniffer::sniffAll(const HTTP &http, Tins::IP::address_type ip)
{
    try
    {
        *_out << http.getHeader("Host") << " from " << ip <<  std::endl;
        // Dump all post data
        for (std::pair<std::string, std::string> data : http.data())
        {
            *_out << "\t" << data.first << " = " << data.second << std::endl;
        }
        *_out << std::endl;
    }
    catch (std::out_of_range &e)
    {
    }
}
