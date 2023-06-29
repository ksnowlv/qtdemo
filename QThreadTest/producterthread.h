#ifndef PRODUCTERTHREAD_H
#define PRODUCTERTHREAD_H

#include <QSemaphore>
#include <QThread>
#include <QMutexLocker>

using namespace std;

class ProducterThread : public QThread
{
    Q_OBJECT
public:
    explicit ProducterThread(QObject *parent = nullptr);
    ~ProducterThread();
public:
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
signals:

private:
    shared_ptr<QSemaphore> producterSemaphore;
    shared_ptr<QSemaphore> consumerSemaphore;
    std::unique_ptr<QMutex> mutex;
    bool exitFlag;
};

#endif // PRODUCTERTHREAD_H
