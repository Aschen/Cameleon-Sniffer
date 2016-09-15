#include "ModuleWorker.hh"

#include "Debug.hh"

ModuleWorker::ModuleWorker()
    : m_module(nullptr)
{
    DEBUG("ModuleWorker::ModuleWorker()", false);
}

ModuleWorker::~ModuleWorker()
{
    DEBUG("ModuleWorker::~ModuleWorker()", false);
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

