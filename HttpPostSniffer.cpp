#include "HttpPostSniffer.hh"

HttpPostSniffer::HttpPostSniffer(Core &core, std::ostream *out, const std::string &filename, const std::vector<std::string> &keys)
    : ASniffer(core, "HttpPostSniffer", "tcp and dst port 80", out), _filename(filename), _hostname("All"), _type(HttpPostSniffer::KEYS), _keys(keys) // put dst and src port 80 for HttpModifier ?
{
}

HttpPostSniffer::HttpPostSniffer(Core &core, std::ostream *out, const std::string &filename, const std::string &hostname)
    : ASniffer(core, "HttpPostSniffer", "tcp and dst port 80", out), _filename(filename), _hostname(hostname), _type(HttpPostSniffer::HOSTNAME)
{
}

HttpPostSniffer::HttpPostSniffer(Core &core, std::ostream *out, const std::string &filename)
    : ASniffer(core, "HttpPostSniffer", "tcp and dst port 80", out), _filename(filename), _hostname("All"), _type(HttpPostSniffer::ALL)
{
}

std::string HttpPostSniffer::info(void)
{
    std::string     msg;
    std::string     keys;

    if (_type == HttpPostSniffer::KEYS)
    {
        msg += "Keys = ";
        for (std::string key : _keys)
        {
            msg += key + " ";
        }
    }
    else if (_type == HttpPostSniffer::HOSTNAME)
    {
        msg += "Hostname = " + _hostname;
    }
    else if (_type == HttpPostSniffer::ALL)
    {
        msg += "Hostname = ALL";
    }
    return msg + ", File = " + _filename;
}

std::string HttpPostSniffer::help(void)
{
    return std::string("Start HttpPostSniffer.\n") + "\tOptions : <type> <filename> [keys | hostname]";
}

bool HttpPostSniffer::handler(PDU &pdu)
{
    // EthernetII / IP / TCP
    EthernetII eth = pdu.rfind_pdu<EthernetII>();
    IP ip = eth.rfind_pdu<IP>();
    TCP tcp = ip.rfind_pdu<TCP>();

    Tins::RawPDU::payload_type payload = tcp.rfind_pdu<RawPDU>().payload();
    std::stringstream       ss;

    for (u_int8_t data : payload)
    {
        ss << data;
    }

    HTTP        http(ss);

    if (http.verb() == "POST")
    {        
        if (_type == HttpPostSniffer::KEYS)
            sniffKeys(http, ip.src_addr());
        else if (_type == HttpPostSniffer::HOSTNAME)
            sniffHostname(http, ip.src_addr());
        else if (_type == HttpPostSniffer::ALL)
            sniffAll(http, ip.src_addr());
    }
    return true;
}

void HttpPostSniffer::sniffKeys(HTTP &http, Tins::IP::address_type ip)
{
    try
    {
        *_out << http.getHeader("Host") << " from " << ip << std::endl;
        for (std::string key : _keys)
        {
            *_out << "\t" << key << " = " << http.getValue(key) << std::endl;
        }
        *_out << std::endl;
    }
    catch (std::out_of_range &e)
    {
        // Key not present
    }
}

void HttpPostSniffer::sniffHostname(HTTP &http, Tins::IP::address_type ip)
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
        std::cout << e.what() << std::endl;
    }
}

void HttpPostSniffer::sniffAll(HTTP &http, Tins::IP::address_type ip)
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
