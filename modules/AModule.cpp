#include "AModule.hh"

#include <time.h>

#include "Debug.hh"

AModule::AModule()
{
}

AModule::AModule(const QString & type, const QString & name)
    : m_type(type),
      m_name(name)
{
    this->setObjectName(name + "(" + type + ")");
}

AModule::~AModule()
{
}

const QString &AModule::type() const
{
    return m_type;
}

const QString &AModule::name() const
{
    return m_name;
}

QString AModule::currentDateTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];

    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

    return buf;
}

bool AModule::handler(Tins::PDU &pdu)
{
    Q_UNUSED(pdu)

    return true;
}
