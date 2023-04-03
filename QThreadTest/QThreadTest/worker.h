#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <qmutex>
#include <QMutexLocker>
#include <qtmetamacros.h>

enum WorkerState {
    EWorkerStateStart,
    EWorkerStateRunning,
    EWorkerStateFinish,
};

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);

public:
    const bool getExitFlag() {
        QMutexLocker<QMutex> locker(mutex.get());
        return exitFlag;
    }

    inline void setExitFlag(bool flag) {
        QMutexLocker<QMutex> locker(mutex.get());
        this->exitFlag = flag;
    }

public slots:
    void doWork();

signals:
    void workerResult(WorkerState state, const QString& result);

private:

    std::unique_ptr<QMutex> mutex;
    bool exitFlag;
};

#endif // WORKER_H
