#ifndef DNSSPOOF_HH
# define DNSSPOOF_HH

# include <QMap>

# include <tins/tins.h>

# include "AModule.hh"
# include "daemon/Command.hh"

class DnsSpoof : public AModule
{
    struct Config
    {
        QString     hostsFile;
    };

public:
    static DnsSpoof*  create(const StartModuleArgs & startModuleArgs);
    static Tins::SnifferConfiguration   snifferConfiguration();
    static const QStringList  USAGE;

private:
    Tins::PacketSender      m_packetSender;
    Tins::Sniffer           m_sniffer;
    QMap<QString, QString>  m_spoofedDomains;

public:
    DnsSpoof(const StartModuleArgs & startModuleArgs, const Config & config);

    // AModule interface
public slots:
    void                    start();
    void                    stop();

protected:
    bool                    handler(Tins::PDU & pdu);
};

#endif // DNSSPOOF_HH
