#ifndef QREADWRITELOCKTEST_H
#define QREADWRITELOCKTEST_H

#include <QObject>
#include <qreadwritelock.h>

using namespace std;

class QReadWriteLockTest: QObject
{
    Q_OBJECT
public:
    QReadWriteLockTest();

public:
    void start();
    void stop();

private:
    void readThread();
    void writeThread();

private:
    unique_ptr<QReadWriteLock> rwLock;

    QThread*  threads;
    bool exitFlag;
};

#endif // QREADWRITELOCKTEST_H
