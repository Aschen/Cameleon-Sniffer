#include "BaseSocket.hh"

#include <QByteArray>
#include <QDataStream>

#include "Debug.hh"

BaseSocket::BaseSocket(qint32 socketFd, QObject * parent)
    : QTcpSocket(parent),
      m_socketFd(socketFd)
{
    DEBUG("BaseSocket::BaseSocket() : " << socketFd, false);

    connect(this,   SIGNAL(readyRead()),
            this,   SLOT(readMessage()));
    connect(this,   SIGNAL(disconnected()),
            this,   SLOT(slotDisconnected()));

    connect(this,   SIGNAL(error(QAbstractSocket::SocketError)),
            this,   SLOT(displayError(QAbstractSocket::SocketError)));

}

BaseSocket::~BaseSocket()
{
    DEBUG("BaseSocket::~BaseSocket()", false);
}

QDataStream::Version BaseSocket::streamVersion() const
{
    return QDataStream::Qt_5_0;
}

bool BaseSocket::setDescriptor(qintptr socketFd)
{
    qintptr     descriptor = socketFd == -1 ? m_socketFd : socketFd;

    if ( ! setSocketDescriptor(descriptor))
    {
        DEBUG("BaseSocket::setDescriptor() : Unable to set socket descriptor" << error(), true);
        return false;
    }

    return true;
}

qint32 BaseSocket::fd() const
{
    return m_socketFd;
}

/* PRIVATE SLOT */
void BaseSocket::readMessage()
{
    qint32 availableBytes = bytesAvailable();

    if (availableBytes == 0)
        return;

    m_recvBuffer.append(readAll());

    QDataStream ds(m_recvBuffer);
    ds.setVersion(streamVersion());

    qint32 bufferSize;
    ds >> bufferSize;

    if (ds.status() == QDataStream::ReadPastEnd)
        return;

    while (m_recvBuffer.size() >= (bufferSize + (qint32) sizeof(qint32)))
    {
        QByteArray  rawData;

        ds >> rawData;

        m_recvBuffer.remove(0, bufferSize + (qint32) sizeof(qint32));

        QDataStream variantDs(rawData);
        QVariant    variant;

        variantDs >> variant;

        emit message(m_socketFd, variant);

        ds >> bufferSize;

        if (ds.status() == QDataStream::ReadPastEnd)
            return;

        if (ds.status () != QDataStream::Ok)
            return;
    }
}

void BaseSocket::send(qint32 socketFd, const QVariant & data)
{
    if ( ! (state() == QAbstractSocket::ConnectedState))
        DEBUG("BaseSocket::send() : Socket is not in connected state", true);

    if (isOpen()
        && state() == QAbstractSocket::ConnectedState
        && (socketFd == m_socketFd || socketFd == BROADCAST))
    {
        DEBUG("BaseSocket::send() " << m_socketFd << " : " << data, false);

        sendRaw(prepare(data));
    }
}

void BaseSocket::sendRaw(const QByteArray & data)
{

    QDataStream out(this);

    out.setVersion(streamVersion());
    out << (quint32) data.size() + (qint32) sizeof(quint32);
    out << data;

    flush();
}

void BaseSocket::resetSocket()
{
    m_recvBuffer.remove(0, m_recvBuffer.size());
}

QByteArray BaseSocket::prepare(const QVariant & data) const
{
    QByteArray  rawData;
    QDataStream ds(&rawData, QIODevice::WriteOnly);

    ds.setVersion(streamVersion());
    ds << data;

    return rawData;
}

void BaseSocket::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
        case QAbstractSocket::RemoteHostClosedError:
            break;

        case QAbstractSocket::HostNotFoundError:
            break;

        case QAbstractSocket::ConnectionRefusedError:
            break;

        default:
            break;
    }
    DEBUG("BaseSocket::displayError() : " << errorString(), false);
}

void BaseSocket::slotDisconnected()
{
    emit clientDisconnected(m_socketFd);

    // Only delete socket if it's not a client type
    if (m_socketFd != BROADCAST)
        deleteLater();
}
