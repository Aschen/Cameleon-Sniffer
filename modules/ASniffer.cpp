#include "ASniffer.hh"

ASniffer::ASniffer(const QString & type, const QString & name, const Tins::SnifferConfiguration & snifferConfig)
    : AModule(type, name),
      m_sniffer("wlo1", snifferConfig)
{

}

ASniffer::~ASniffer()
{

}

void ASniffer::start()
{

}

void ASniffer::stop()
{

}

