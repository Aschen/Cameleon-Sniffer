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
    static Tins::SnifferConfiguration   snifferConfiguration();
    static const QStringList  help;

private:
    QFile           m_logFile;
    Tins::Sniffer   m_sniffer;
    QTextStream     m_out;

public:
    DnsWatcher(const QString & name, Config & config);
    virtual ~DnsWatcher();

    // AModule interface
protected:
    bool            handler(Tins::PDU &pdu);

public slots:
    void            start();
    void            stop();
};

#endif // DNSWATCHER_HH
