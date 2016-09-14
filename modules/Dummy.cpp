#include "Dummy.hh"

#include <QTextStream>
#include <QStringList>
#include <QThread>

#include "Debug.hh"

Dummy *Dummy::create(const QString & name, const QStringList & args)
{
    if (args.size() < 1)
    {
        return nullptr;
    }

    qint32      dummyness = args[0].toInt();

    return new Dummy(name, dummyness);
}

QStringList Dummy::help()
{
    QStringList message;

    message << "Dummy module usage :";
    message << "\t cameleon start Dummy <module name> <dummyness>";

    return message;
}

Dummy::Dummy(const QString & name, qint32 dummyness)
    : AModule("Dummy", name),
      m_dummyness(dummyness)
{
    m_timer.setSingleShot(false);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(hello()));
}

Dummy::~Dummy()
{
    DEBUG("Dummy::~Dummy()", true);
}

void Dummy::start()
{
    DEBUG("Dummy::start()", true);
    m_timer.start(1000);
}

void Dummy::stop()
{
    DEBUG("Dummy::stop()", true);
    m_timer.stop();
}

bool Dummy::handler(Tins::PDU &pdu)
{
    DEBUG("Dummy::handler()", true);
    return true;
}

void Dummy::hello()
{
    QTextStream out(stdout);

    out << this->thread()->objectName() << " : Hello from " << m_name << " (" << m_type << ")";
    out << " dummyness:" << m_dummyness;
    out << "\n";
}

