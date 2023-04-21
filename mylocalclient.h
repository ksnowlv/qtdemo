#ifndef MYLOCALCLIENT_H
#define MYLOCALCLIENT_H

#include <QObject>
#include <QLocalSocket>

using namespace std;

class MyLocalClient : public QObject
{
    Q_OBJECT
public:
    explicit MyLocalClient(QObject *parent = nullptr);
    ~MyLocalClient();

signals:

private slots:
    void handleReceiveData();
    void handleSocketError(QLocalSocket::LocalSocketError socketError);


private:
    QLocalSocket *socket;
};

#endif // MYLOCALCLIENT_H
