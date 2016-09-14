#include <QCoreApplication>
#include "Sender.hh"

int main(int argc, char *argv[])
{
    QCoreApplication    a(argc, argv);

    if (argc <= 1)
    {
        qDebug() << "You must provide a message for the daemon";
        return 1;
    }

    Sender      sender("localhost", 4242);

    if ( ! sender.start())
        return 1;

    QString     message;

    for (int i = 1; i < argc; ++i)
        message += argv[i];

    sender.send(message);

    return a.exec();
}

