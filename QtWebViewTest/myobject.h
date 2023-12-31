#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QObject>
#include <QDebug>

class MyObject : public QObject
{
    Q_OBJECT
public:
    explicit MyObject(QObject *parent = nullptr);

public slots:
    void showMessage(const QString &message);

 public slots:
    void callNativeMethod(const QString &message);
signals:
    void nativeMethodCalled(const QString &message);
};

#endif // MYOBJECT_H
