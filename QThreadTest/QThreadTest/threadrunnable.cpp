#include "threadrunnable.h"
#include <iostream>
#include <QThread>

using namespace std;

ThreadRunnable::ThreadRunnable(QObject *parent)
    : QObject{parent}
{

}

void ThreadRunnable::run() {
    cout<<QThread::currentThread()<<"线程被调用"<<endl;
    emit completeEvent(1);
}

void ThreadRunnable::revMessageFromMain(const QString& message) {
    cout<<"子线程:"<<QThread::currentThread()<<"收到消息："<<message.toStdString()<<endl;
}
