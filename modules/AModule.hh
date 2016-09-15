#ifndef AMODULE_HH
# define AMODULE_HH

# include <QObject>
# include <QString>
# include <QDebug>

# include <tins/pdu.h>

class AModule : public QObject
{
    Q_OBJECT

protected:
    const QString           m_type;
    const QString           m_name;

public:
    AModule();
    AModule(const QString & type, const QString & name);
    virtual ~AModule();

public slots:
    virtual void            start() = 0;
    virtual void            stop() = 0;

    const QString&          type() const;
    const QString&          name() const;

protected:
    QString                 currentDateTime();

protected:
    virtual bool            handler(Tins::PDU & pdu);
};

#endif // AMODULE_HH
