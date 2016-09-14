#include "AModule.hh"

AModule::AModule(const QString & type, const QString & name)
    : m_type(type),
      m_name(name)
{
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

void AModule::hello()
{
    qDebug() << "This is broken";
}

