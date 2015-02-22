#include "DnsDump.hh"

DnsDump::DnsDump(Core &core)
    : ASniffer(core, "DnsDump", "udp and dst port 53")
{
}

bool DnsDump::dumpQuery(PDU &pdu)
{
    // EthernetII / IP / UDP / RawPDU
    EthernetII eth = pdu.rfind_pdu<EthernetII>();
    IP ip = eth.rfind_pdu<IP>();
    UDP udp = ip.rfind_pdu<UDP>();
    DNS dns = udp.rfind_pdu<RawPDU>().to<DNS>();

    // Is it a DNS query?
    if(dns.type() == DNS::QUERY)
    {
        // Let's see if there's any query for an "A" record.
        for(const DNS::Query &query : dns.queries())
        {
            if(query.type() == DNS::A)
            {
                std::cout << ip.src_addr() << " query " << query.dname() << std::endl;
            }
        }
    }
    return true;
}

void DnsDump::sniff(void)
{
    _sniffer.sniff_loop(make_sniffer_handler(this, &DnsDump::dumpQuery));
}

void DnsDump::start(void)
{
    std::cout << "Start DNS dumping" << std::endl;
    std::thread     t(&DnsDump::sniff, this);

    t.detach();
}

void DnsDump::stop(void)
{
    _sniffer.stop_sniff();
}

std::string DnsDump::info(void)
{
    return "Dump all DNS queries";
}
