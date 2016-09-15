#ifndef SOCKETWORKER_HH
# define SOCKETWORKER_HH

# include <QVariant>
# include <QSharedPointer>

# include "daemon/AbstractWorker.hpp"
# include "BaseSocket.hh"

class SocketWorker : public AbstractWorker<QObject>
{
    Q_OBJECT

private:
    QSharedPointer<BaseSocket>  m_socket;

public:
    SocketWorker();
    ~SocketWorker();

    void        setSocket(BaseSocket * socket);

public slots:
    void        start() Q_DECL_OVERRIDE;
    void        stop() Q_DECL_OVERRIDE;
};

#endif // SOCKETWORKER_HH
