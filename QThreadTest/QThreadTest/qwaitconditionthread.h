#ifndef QWAITCONDITIONTHREAD_H
#define QWAITCONDITIONTHREAD_H

#include <QObject>

class QWaitConditionThread : public QObject
{
    Q_OBJECT
public:
    explicit QWaitConditionThread(QObject *parent = nullptr);

signals:

};

#endif // QWAITCONDITIONTHREAD_H
