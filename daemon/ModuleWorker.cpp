#include "ModuleWorker.hh"

#include "Debug.hh"

ModuleWorker::ModuleWorker()
    : m_module(nullptr)
{
}

ModuleWorker::~ModuleWorker()
{
}

void ModuleWorker::setModule(AModule * module)
{
    m_module = QSharedPointer<AModule>(module);
}

void ModuleWorker::start()
{
    m_module->start();
}

void ModuleWorker::stop()
{
    m_module->stop();
}

