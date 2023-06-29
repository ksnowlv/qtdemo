#ifndef THREADCONTROLOBJECT_H
#define THREADCONTROLOBJECT_H

#include <QThread>
#include <qobject>
#include <qsemaphore.h>
#include "worker.h"

//实现线程的互斥与同步常使用的类有 QMutex、QMutexLocker、 QReadWriteLocker、
//QReadLocker、QWriteLocker、QSemaphore 和 QWaitCondition。


using namespace std;

class ThreadControlObject : public QObject
{
    Q_OBJECT
public:
    explicit ThreadControlObject(QObject *parent = nullptr);
    ~ThreadControlObject();

public:
    void threadStart();
    void threadStop();
    void concurrentStart();
private:
    void init();

signals:
    void workerResult(const QString& result);

private:
    unique_ptr<QThread> processThread;
    unique_ptr<Worker> worker;
};

#endif // THREADCONTROLOBJECT_H
