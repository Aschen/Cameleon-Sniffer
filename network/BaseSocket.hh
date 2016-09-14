#ifndef BASESOCKET_HH
# define BASESOCKET_HH

# include <QTcpSocket>
# include <QVariant>
# include <QDataStream>
# include <QByteArray>

/**
 * @class BaseSocket
 * @brief Represent a socket endpoint connected to an other throught network
 *
 */
class BaseSocket : public QTcpSocket
{
    Q_OBJECT

public:
    enum Destination
    {
        BROADCAST = -1
    };

protected:
    const qint32    m_socketFd;
    QByteArray      m_recvBuffer;

public:
    BaseSocket(qint32 socketFd, QObject * parent = nullptr);
    virtual ~BaseSocket();

    QByteArray      prepare(const QVariant & data) const;
    void            sendRaw(const QByteArray & data);

    void            resetSocket();

    QDataStream::Version    streamVersion() const;
    bool            setDescriptor(qintptr socketFd = -1);
    qint32          fd() const;

signals:
    void            message(qint32 socketFd, const QVariant & data);
    void            clientDisconnected(qint32 socketFd);

public slots:
    void            send(qint32 socketFd, const QVariant & data);

private slots:
    void            readMessage();
    void            displayError(QAbstractSocket::SocketError socketError);

    /**
     * @brief Ugly hack to send signal clientDisconnected() with the socket descriptor
     */
    void            slotDisconnected();

};


#endif // BASESOCKET_HH
