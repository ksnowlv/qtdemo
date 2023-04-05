#include "consumerthread.h"
#include <iostream>

ConsumerThread::ConsumerThread(QObject *parent)
    :QThread(parent)
    ,exitFlag(false)
    ,mutex(std::make_unique<QMutex>())
{

}

void ConsumerThread::run() {

    while(true) {

        if(consumerSemaphore->tryAcquire()) {
            cout<<"---ConsumerThread"<<this_thread::get_id()<<endl;
            producterSemaphore->release();
        }
        this_thread::sleep_for(chrono::seconds(2));

         //QMutexLocker<QMutex> locker(mutex.get());
        if(exitFlag){
            cout<<"ConsumerThread exitFlag"<<endl;
            break;
        }
    }
}

void ConsumerThread::exit() {
    setExitFlag(true);
    quit();
    wait();
}
