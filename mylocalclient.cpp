#include "mylocalclient.h"
#include <iostream>
using namespace std;

MyLocalClient::MyLocalClient(QObject *parent)
    : QObject{parent}
{
    socket = new QLocalSocket(this);
}

MyLocalClient::~MyLocalClient() {
    if(socket) {
        socket->abort();
    }
}


void MyLocalClient::handleReceiveData() {
    if(socket) {
        const QByteArray& ba = socket->readAll();
        const QString& s = QString(ba);
        cout<<"handleReceiveData rev data:"<<s.toStdString()<<endl;
    }
}

void MyLocalClient::handleSocketError(QLocalSocket::LocalSocketError socketError) {
    switch (socketError) {
      case QLocalSocket::ServerNotFoundError:
        cout<<"ServerNotFoundError"<<endl;
          break;
      case QLocalSocket::ConnectionRefusedError:
        cout<<"ConnectionRefusedError"<<endl;
          break;
      case QLocalSocket::PeerClosedError:
        cout<<"PeerClosedError"<<endl;
          break;
      default:
        cout<<"handleSocketError default"<<endl;
          break;
    }
}
