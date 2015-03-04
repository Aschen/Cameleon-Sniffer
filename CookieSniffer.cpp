#include "CookieSniffer.hh"

CookieSniffer::CookieSniffer(const NetworkInterface &interface, std::ostream *out, const std::string &filename, const std::vector<std::string> &keys)
    : ASniffer(interface, "CookieSniffer", "tcp and dst port 80", out), _filename(filename), _keys(keys)
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
    std::string value;

    try
    {        
        for (std::string key : _keys)
        {
            value = http.getCookie(key); // Throw exception if key not exist
            *_out << http.getHeader("Host") << "\t" << key << " = " << value << std::endl;
        }
    }
    catch (std::out_of_range &e)
    {
        // Key not present
    }
    return true;
}

std::string CookieSniffer::info(void) const
{
    std::string     keys;

    for (std::string key : _keys)
        keys += key + " ";

    return "Keys = " + keys + ", File =  " + _filename;
}

std::string CookieSniffer::help(void) { return std::string("Start CookieSniffer.\n") + "\tOptions : <filename> [keys]"; }
