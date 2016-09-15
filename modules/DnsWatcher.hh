#ifndef DNSWATCHER_HH
# define DNSWATCHER_HH

# include <QFile>
# include <QTextStream>

# include <tins/tins.h>

# include "daemon/Command.hh"
# include "AModule.hh"

class DnsWatcher : public AModule
{
    struct Config
    {
        QString         filepath;
    };

public:
    static DnsWatcher*  create(const StartModuleArgs & startModuleArgs);
    static Tins::SnifferConfiguration   snifferConfiguration();
    static const QStringList  USAGE;

private:
    QFile           m_logFile;
    Tins::Sniffer   m_sniffer;
    QTextStream     m_out;

public:
    DnsWatcher(const StartModuleArgs & startModuleArgs, const Config & config);
    ~DnsWatcher();

    // AModule interface
protected:
    bool            handler(Tins::PDU &pdu);

public slots:
    void            start();
    void            stop();
};

#endif // DNSWATCHER_HH
