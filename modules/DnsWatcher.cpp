#include "DnsWatcher.hh"

#include <QThread>

#include "Debug.hh"

DnsWatcher *DnsWatcher::create(const QString &name, const QStringList &args)
{
    if (args.size() < 1)
    {
        return nullptr;
    }

    DnsWatcher::Config  config;

    config.filepath = args[0];

    return new DnsWatcher(name, config);

}

Tins::SnifferConfiguration DnsWatcher::snifferConfiguration()
{
    Tins::SnifferConfiguration  config;

    config.set_filter("dst port 53");
    config.set_promisc_mode(true);

    return config;
}

const QStringList DnsWatcher::help = { "DnsWatcher module usage :",
                                       "\t cameleon start DnsWatcher <module name> <filepath>"
                                     };

/* Class DnsWatcher **********************************************************/

DnsWatcher::DnsWatcher(const QString & name, Config & config)
    : AModule("DnsWatcher", name),
      m_logFile(config.filepath),
      m_sniffer("wlo1", DnsWatcher::snifferConfiguration()),
      m_out(&m_logFile)
{
}

DnsWatcher::~DnsWatcher()
{
    DEBUG("DnsWatcher::~DnsWatcher()", true);
}

bool DnsWatcher::handler(Tins::PDU & pdu)
{
    // EthernetII / IP / UDP / RawPDU
    Tins::EthernetII eth = pdu.rfind_pdu<Tins::EthernetII>();
    Tins::IP ip = eth.rfind_pdu<Tins::IP>();
    Tins::UDP udp = ip.rfind_pdu<Tins::UDP>();
    Tins::DNS dns = udp.rfind_pdu<Tins::RawPDU>().to<Tins::DNS>();

    // Is it a DNS query?
    if(dns.type() == Tins::DNS::QUERY)
    {
        // Let's see if there's any query for an "A" record.
        for(const Tins::DNS::Query &query : dns.queries())
        {
            if(query.type() == Tins::DNS::A)
            {
                m_out << "\t" << QString::fromStdString(ip.src_addr().to_string()) << "  -->  " << QString::fromStdString(query.dname()) << "\n";
                m_out.flush();
            }
        }
    }
    return true;
}

void DnsWatcher::start()
{
    DEBUG("DnsWatcher::start() : Name:" << m_name, true);
    if ( ! m_logFile.open(QIODevice::ReadWrite))
    {
        DEBUG("DnsWatcher::start() : Can't open file", true);
        return;
    }

    m_sniffer.sniff_loop(Tins::make_sniffer_handler(this, &DnsWatcher::handler));

    DEBUG("DnsWatcher::start() : after sniff_loop()" << m_name, true);
}

void DnsWatcher::stop()
{
    DEBUG("DnsWatcher::stop()", true);
    m_sniffer.stop_sniff();
}
