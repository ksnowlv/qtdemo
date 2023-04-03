#include "threadcontrolobject.h"
#include<iostream>
#include <QtConcurrent/QtConcurrent>
using namespace std;

ThreadControlObject::ThreadControlObject(QObject *parent)
    :QObject(parent)
{

}

ThreadControlObject::~ThreadControlObject() {
    threadStop();
}

void ThreadControlObject::threadStart() {
    init();
}

void ThreadControlObject::threadStop() {

    if(worker) {
        worker->setExitFlag(true);
    }

    if(processThread) {
        processThread->quit();
        processThread->wait();
    }
}

void ThreadControlObject::concurrentStart() {
    QFuture<QString> future =  QtConcurrent::run([](int type, const QString& msg) -> QString{

        return QString::number(type) + msg;
    }, 1, "hello QtConcurrent!");

    const QString& result =  future.result();
    future.waitForFinished();
    cout<<__func__<<" result:"<<result.toStdString()<<endl;
}


void ThreadControlObject::init() {
    processThread.reset(nullptr);
    processThread = make_unique<QThread>();
    worker.reset(nullptr);
    worker = make_unique<Worker>();
    worker->moveToThread(processThread.get());


//    void (Worker::*doWork)(const QString&)=&Worker::doWork;

//    connect(processThread.get(),
//            &QThread::start,
//            worker.get(),
//            doWork);
    connect(processThread.get(),
            &QThread::started,
            worker.get(),
            &Worker::doWork);

    connect(processThread.get(),
            &QThread::destroyed,
            this,
            []() {

    });

    connect(worker.get(),
            &Worker::workerResult,
            this,
            [&](WorkerState state, const QString& message) {
            cout<<"state:"<<QString::number(state).toStdString()<<",message:" <<message.toStdString()<<endl;
            emit workerResult(message);

            cout<<"+++"<<__func__<<this_thread::get_id()<<endl;
    });

    processThread->start();
}
