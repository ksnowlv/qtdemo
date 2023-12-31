#ifndef CUSTOMCLASS_H
#define CUSTOMCLASS_H

#include <QObject>

class CustomClass : public QObject
{
    Q_OBJECT
public:
    explicit CustomClass(QObject *parent = nullptr);

public:
    void handleSendMessage();

signals:
    void showMessage(const QString &message);

private:
    int count;
};

#endif // CUSTOMCLASS_H
