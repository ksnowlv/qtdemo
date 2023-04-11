#ifndef THREADPOOLTEST_H
#define THREADPOOLTEST_H

#include <QObject>
#include <QThreadPool>
#include "threadrunnable.h"

using namespace std;

class ThreadRunnable;

class ThreadPoolTest : public QObject
{
    Q_OBJECT
public:
    explicit ThreadPoolTest(QObject *parent = nullptr);
    ~ThreadPoolTest();

    void startTask();
signals:
    void sendMessageToThread(const QString& message);

private:

    unique_ptr<QThreadPool> pool;
    //unique_ptr<ThreadRunnable[]> runnableTasks;
    ThreadRunnable*  runnableTasks;

};

#endif // THREADPOOLTEST_H
