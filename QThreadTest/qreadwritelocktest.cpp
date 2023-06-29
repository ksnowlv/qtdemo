#include "qreadwritelocktest.h"
#include <iostream>
#include <qthread.h>

const int THREAD_NUM = 5;

QReadWriteLockTest::QReadWriteLockTest()
{
    rwLock = std::make_unique<QReadWriteLock>();

    threads = new QThread[THREAD_NUM];

    for (int i = 0; i < THREAD_NUM - 1; ++i) {

        QObject::connect(&threads[i], &QThread::started, [&]() {
            readThread();
        });
    }

    QObject::connect(&threads[THREAD_NUM - 1], &QThread::started, [&]() {
        writeThread();
    });
}

void QReadWriteLockTest::readThread() {

    while (true) {
        rwLock->lockForRead();
        cout<<"Read"<<QThread::currentThread()<<"Running!"<<endl;
        rwLock->unlock();
        if(exitFlag) {
            break;
        }

        QThread::msleep(1000);
    }
}

void QReadWriteLockTest::writeThread() {
    while (true) {
        rwLock->lockForWrite();
        cout<<"Write:"<<QThread::currentThread()<<"Running!"<<endl;
        rwLock->unlock();
        if(exitFlag) {
            break;
        }
        QThread::msleep(1000);
    }
}

void QReadWriteLockTest::start() {

    exitFlag = false;
    for (int i = 0; i < THREAD_NUM; ++i) {
        threads[i].start();
    }
}

void QReadWriteLockTest::stop() {
    exitFlag = true;

    for (int i = 0; i < THREAD_NUM; ++i) {
        threads[i].quit();
        threads[i].wait();
    }
}


