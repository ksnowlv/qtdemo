#include "worker.h"
#include <iostream>
#include <thread>


using namespace std;

Worker::Worker(QObject *parent)
    : QObject{parent},
      mutex(std::make_unique<QMutex>())
{

}

void Worker::doWork() {
    cout<<__func__<<" is called!"<<endl;


    emit workerResult(EWorkerStateStart,"---work start");



    for (int i = 0; i < 100; ++i) {

        QMutexLocker<QMutex> locker(mutex.get());
        const QString& s = "do Work:" + QString::number(i + 1);
        cout<<"Worker doWork" <<s.toStdString()<<endl;
        emit workerResult(EWorkerStateRunning, s);
        if(exitFlag) {
            break;
        }
        this_thread::sleep_for(chrono::seconds(1));
    }

    emit workerResult(EWorkerStateFinish,"---work finish");
    cout<<"---work finish---"<<__func__<<this_thread::get_id()<<endl;
}






