#include "ModuleWorker.hh"

ModuleWorker::ModuleWorker()
    : m_module(nullptr)
{
}

void ModuleWorker::setModule(AModule * module)
{
    m_module = module;
}

void ModuleWorker::start()
{
    if (m_module)
    {
        m_module->start();
    }
}

void ModuleWorker::stop()
{
    if (m_module)
    {
        m_module->stop();
    }
}

