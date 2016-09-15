#ifndef SERVER_HH
# define SERVER_HH

# include <QTcpServer>
# include <QSharedPointer>

# include "SocketWorker.hh"

class Core;

class Server : public QTcpServer
{
    Q_OBJECT

private:
    quint16                         m_port;
    QHostAddress                    m_listenAddress;
    QSharedPointer<SocketWorker>    m_worker;
    Core*                           m_core;

public:
    Server(quint16 port, Core * core);
    ~Server();

    void                start();

    void                sendResponse(const QVariant & data);

public slots:
    void                clientDisconnected(qint32 socketFd);
    void                receiveMessage(qint32 socketFd, const QVariant & message);

signals:
    void                send(qint32 socketFd, const QVariant & data) const;
    void                messageReceived(const QVariant & data);

    // QTcpServer interface
protected:
    void                incomingConnection(qintptr socketFd);
};

#endif // SERVER_HH
