#ifndef DNSWATCHER_HH
# define DNSWATCHER_HH

# include <QFile>
# include <QTextStream>

# include <tins/tins.h>

# include "AModule.hh"

class DnsWatcher : public AModule
{
    struct Config
    {
        QString         filepath;
    };

public:
    static DnsWatcher*  create(const QString & name, const QStringList & args);
    static QStringList  help();
    static Tins::SnifferConfiguration   snifferConfiguration();

private:
    QFile           m_logFile;
    Tins::Sniffer   m_sniffer;
    QTextStream     m_out;

public:
    DnsWatcher(const QString & name, Config & config);
    virtual ~DnsWatcher();

    // AModule interface
public:
    void            start();
    void            stop();

protected:
    bool            handler(Tins::PDU &pdu);
};

#endif // DNSWATCHER_HH
