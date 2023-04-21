#ifndef MYLOCALSERVER_H
#define MYLOCALSERVER_H

#include <QObject>
#include <qlocalserver.h>
#include <qvector.h>

using namespace std;

class MyLocalServer : public QObject
{
    Q_OBJECT
public:
    explicit MyLocalServer(QObject *parent = nullptr);
    ~MyLocalServer();

    void startServer();

signals:

public slots:
    void handleNewConnection();

    void handleDisconnect();

    void handleReadData();

private:

    unique_ptr<QLocalServer> server;
    QVector<QLocalSocket*> socketList;


};

#endif // MYLOCALSERVER_H
