#include "Server.hh"

#include "daemon/WorkerFactory.hpp"
#include "SocketWorker.hh"
#include "daemon/Core.hh"
#include "Debug.hh"

Server::Server(quint16 port, Core *core)
    : m_port(port),
      m_listenAddress(QHostAddress::Any),
      m_core(core)
{
    SocketWorker*   worker = WorkerFactory<SocketWorker>::create(nullptr, "SocketWorker");
    m_worker = QSharedPointer<SocketWorker>(worker);
}

Server::~Server()
{
    m_worker->thread()->quit();
}

void Server::start()
{
    if (isListening())
        return;

    if ( ! listen(m_listenAddress, m_port))
    {
        DEBUG("Server::start() : Server error listen", true);
        return;
    }

    WorkerFactory<SocketWorker>::go(m_worker.data());

    DEBUG("Server::start() : Listening on port" << m_port, true);
}

void Server::sendResponse(const QVariant & data)
{
    emit send(BaseSocket::BROADCAST, data);
}

void Server::clientDisconnected(qint32 socketFd)
{
    DEBUG("Server::clientDisconnected() : Client" << socketFd, false);
}

void Server::receiveMessage(qint32 socketFd, const QVariant & message)
{
    DEBUG("Server::receiveMessage() : Client" << socketFd << " Message:" << message, false);

    m_core->commandDispatcher(message);
}

void Server::incomingConnection(qintptr socketFd)
{
    BaseSocket*     socket = new BaseSocket(socketFd);

    socket->setDescriptor();

    m_worker->setSocket(socket);

    connect(socket, SIGNAL(clientDisconnected(qint32)),
            this,   SLOT(clientDisconnected(qint32)));

    connect(socket, SIGNAL(messageReceived(qint32, QVariant)),
            this,   SLOT(receiveMessage(qint32, QVariant)));

    connect(this,   SIGNAL(send(qint32, QVariant)),
            socket, SLOT(send(qint32, QVariant)));
}

