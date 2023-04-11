#include "qwaitconditionthread.h"
#include <QMutexLocker>
#include <iostream>
#include <QRandomGenerator>

using namespace std;

QWaitConditionThread::QWaitConditionThread(QObject *parent)
    : QThread{parent}
    , exitFlag(false) {
    mutex = std::make_unique<QMutex>();
}


void QWaitConditionThread::run() {
    if(nullptr == waitCondition) {
        return;
    }

    while(!exitFlag && !isInterruptionRequested() ){

        QMutexLocker<QMutex> locker(mutex.get());

        cout<<"线程:"<<this_thread::get_id()<<"进入等待"<<endl;
        waitCondition->wait(mutex.get());
        int time = QRandomGenerator::global()->bounded(10) * 1000;
        cout<<"线程:"<<this_thread::get_id()<<"已唤醒  进入延时"<<time<<"ms"<<endl;
        msleep(time);
    }
}
