#ifndef DUMMY_HH
# define DUMMY_HH

# include <QTimer>

# include "AModule.hh"

class Dummy : public AModule
{
private:
    QTimer          m_timer;

public:
    Dummy(const QString & name);

    // AModule interface
public:
    void            start();
    void            stop();

protected:
    bool            handler(Tins::PDU &pdu);

private slots:
    void            hello();
};

#endif // DUMMY_HH
