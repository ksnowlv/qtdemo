#ifndef CONSUMERTHREAD_H
#define CONSUMERTHREAD_H

#include <QThread>
#include <QSemaphore>
using namespace  std;


class ConsumerThread : public QThread
{
public:
    explicit ConsumerThread(QObject *parent = nullptr);

    inline void setSemaphore(const shared_ptr<QSemaphore>& producterSemaphore, const shared_ptr<QSemaphore>& consumerSemaphore) {
        this->producterSemaphore = producterSemaphore;
        this->consumerSemaphore = consumerSemaphore;
    }

    inline void setExitFlag(bool exitFlag) {
        //QMutexLocker<QMutex> locker(mutex.get());
        this->exitFlag = exitFlag;
    }

public:
    void run();

    void exit();

private:
    shared_ptr<QSemaphore> producterSemaphore;
    shared_ptr<QSemaphore> consumerSemaphore;
    std::unique_ptr<QMutex> mutex;
    bool exitFlag;
};

#endif // CONSUMERTHREAD_H
