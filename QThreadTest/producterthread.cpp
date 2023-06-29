#include "producterthread.h"
#include <iostream>

ProducterThread::ProducterThread(QObject *parent)
    : QThread(parent)
    ,exitFlag(false)
    ,mutex(std::make_unique<QMutex>())
{

}

ProducterThread::~ProducterThread() {

}


void ProducterThread::run() {

    while(true) {

        if(producterSemaphore->tryAcquire()) {
            cout<<"ProducterThread---"<<this_thread::get_id()<<endl;
            consumerSemaphore->release();
        }
        this_thread::sleep_for(chrono::seconds(1));

        //QMutexLocker<QMutex> locker(mutex.get());
        if(exitFlag) {
            cout<<"ProducterThread exitFlag"<<endl;
            break;
        }
    }
}

void ProducterThread::exit() {
    setExitFlag(true);
    quit();
    wait();
}
