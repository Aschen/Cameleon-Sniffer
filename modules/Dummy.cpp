#include "Dummy.hh"

#include <QTextStream>
#include <QThread>

#include "Debug.hh"

Dummy::Dummy(const QString & name)
    : AModule("Dummy", name)
{
    m_timer.setSingleShot(false);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(hello()));
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

    out << this->thread()->objectName() << " : Hello from " << m_name << " (" << m_type << ")" << "\n";
}

