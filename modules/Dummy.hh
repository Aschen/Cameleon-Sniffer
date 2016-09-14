#ifndef DUMMY_HH
# define DUMMY_HH

# include <QTimer>
# include <QStringList>

# include "AModule.hh"

class Dummy : public AModule
{
public:
    static Dummy *      create(const QString & name, const QStringList & args);
    static QStringList  help();

private:
    qint32          m_dummyness;
    QTimer          m_timer;

public:
    Dummy(const QString & name, qint32 dummyness);
    virtual ~Dummy();

    // AModule interface
public:
    void            start();
    void            stop();

protected:
    bool            handler(Tins::PDU & pdu);

private slots:
    void            hello();
};

#endif // DUMMY_HH
