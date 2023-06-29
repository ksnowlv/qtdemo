#ifndef THREADRUNNABLE_H
#define THREADRUNNABLE_H

#include <QObject>
#include <qrunnable.h>


class ThreadRunnable : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit ThreadRunnable(QObject *parent = nullptr);

public:
    void run() override;

public:
    inline void setExitFlag(const bool exitFlag) {
        this->exitFlag = exitFlag;
    }

signals:
    void completeEvent(const int type);

public slots:

    void revMessageFromMain(const QString& message);

private:
    bool exitFlag;

};

#endif // THREADRUNNABLE_H
