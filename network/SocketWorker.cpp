#include "SocketWorker.hh"

#include "Debug.hh"

SocketWorker::SocketWorker()
{
}

SocketWorker::~SocketWorker()
{
}

void SocketWorker::setSocket(BaseSocket * socket)
{
    socket->moveToThread(this->thread());
}

void SocketWorker::start()
{
    DEBUG("SocketWorker::start()", false);
}

void SocketWorker::stop()
{
    DEBUG("SocketWorker::stop()", true);
}
