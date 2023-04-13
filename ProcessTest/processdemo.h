#ifndef PROCESSDEMO_H
#define PROCESSDEMO_H

#include <QObject>
#include <QProcess>

using namespace std;

class QProcess;

class ProcessDemo : public QObject
{
    Q_OBJECT
public:
    ProcessDemo();

public:
    void start();

private:

    unique_ptr<QProcess> process;

};

#endif // PROCESSDEMO_H
