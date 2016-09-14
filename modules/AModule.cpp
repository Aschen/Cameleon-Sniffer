#include "AModule.hh"

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

bool AModule::handler(Tins::PDU &pdu)
{
    Q_UNUSED(pdu)

    return true;
}
