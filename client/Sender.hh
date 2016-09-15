#ifndef SENDER_HH
# define SENDER_HH

# include <QTextStream>
# include <QVariant>
# include <QFile>
# include <QVector>

# include "../network/BaseSocket.hh"

class Sender : public QObject
{
    Q_OBJECT

private:
    QString             m_host;
    quint16             m_port;
    BaseSocket*         m_socket;
    QVector<QVariant>   m_messages;

public:
    Sender(const QString & host, quint16 port, QObject * parent = nullptr);
    Sender(QObject * parent = nullptr);
    ~Sender();

    bool                start();
    bool                start(const QString & host, quint16 port);
    void                stop();

    void                send(const QVariant & data);

    const BaseSocket*   socket() const;
    void                hostname(const QString & host);
    void                port(quint16 port);

private:
    void                init();

signals:
    void                transfertMessage(qint32 socketFd, const QVariant & msg);

public slots:
    void                receiveMessage(qint32 socketFd, const QVariant & msg);

private slots:
    void                socketError(QAbstractSocket::SocketError socketError);
    void                sendWaitingMessages();
};

#endif // SENDER_HH
