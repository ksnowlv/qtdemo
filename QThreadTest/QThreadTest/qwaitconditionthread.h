#ifndef QWAITCONDITIONTHREAD_H
#define QWAITCONDITIONTHREAD_H

#include <QObject>
#include <QWaitCondition>
#include <qthread.h>
#include <qmutex.h>

class QWaitConditionThread : public QThread
{
    Q_OBJECT
public:
    explicit QWaitConditionThread(QObject *parent = nullptr);

    inline void setWaitCondition(std::shared_ptr<QWaitCondition> waitCondition) {
        this->waitCondition = waitCondition;
    }

    inline void setExitFlag(bool exitFlag) {
        this->exitFlag = exitFlag;
    }

    inline bool getExitFlag() const  {
        return exitFlag;
    }

private:
    void run() override;

signals:

private:
    std::unique_ptr<QMutex> mutex;
    std::shared_ptr<QWaitCondition> waitCondition;
    bool exitFlag;

};

#endif // QWAITCONDITIONTHREAD_H
