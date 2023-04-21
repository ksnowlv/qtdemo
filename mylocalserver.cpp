#include "mylocalserver.h"
#include <iostream>
#include <qlocalsocket.h>

using namespace std;

const QString SERVER_NAME = "LocalServer";

MyLocalServer::MyLocalServer(QObject *parent)
    : QObject{parent}
{
    server = make_unique<QLocalServer>();
    QLocalServer::removeServer(SERVER_NAME);
    connect(server.get(),
                      &QLocalServer::newConnection,
                      this,
                      &MyLocalServer::handleNewConnection);
}

MyLocalServer::~MyLocalServer() {

    if(server) {
        server->close();
        server.reset(nullptr);
        server = nullptr;
    }

}

void MyLocalServer::startServer() {

    if(!server->listen(SERVER_NAME)){
         cout<<"server listen failed!"<<server->errorString().toStdString()<<endl;
    }
}


void MyLocalServer::handleNewConnection() {

    cout<<"LocalServer processNewConnection"<<endl;

    if(nullptr == server) {
        return;
    }

    QLocalSocket *clientConnection = server->nextPendingConnection();
    //localSocketList.append(clientConnection);
    connect(clientConnection,
            &QLocalSocket::readyRead,
            this,
            &MyLocalServer::handleReadData);
    connect(clientConnection,
            &QLocalSocket::disconnected,
            this,
            &MyLocalServer::handleDisconnect);
}

void MyLocalServer::handleDisconnect() {

    for (int i = 0; i < socketList.size(); ++i) {
        if(socketList[i]->state() != QLocalSocket::ConnectedState) {
            socketList[i]->deleteLater();
            socketList.removeAt(i);
        }
    }
}

void MyLocalServer::handleReadData() {

}
