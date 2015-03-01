#include "HttpPostSniffer.hh"

HttpPostSniffer::HttpPostSniffer(Core &core, std::ostream *out, const std::string &filename, const std::vector<std::string> &keys)
    : ASniffer(core, "HttpPostSniffer", "tcp and dst port 80", out), _filename(filename), _keys(keys) // put dst and src port 80 for HttpModifier ?
{
}

std::string HttpPostSniffer::info(void)
{
    std::string     keys;

    for (std::string key : _keys)
    {
        keys += key + " ";
    }
    return "Keys : " + keys + " && File :  " + _filename;
}

std::string HttpPostSniffer::help(void)
{
    return std::string("Start HttpPostSniffer.\n") + "\tOptions : <filename> [keys]";
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
        try
        {
            for (std::string key : _keys)
            {
                *_out << http.getHeader("Host") << std::endl;
                *_out << "\t" << key << " -> " << http.getValue(key) << std::endl;
            }
        }
        catch (std::out_of_range &e)
        {
            // Key not present
        }
    }
    return true;
}
