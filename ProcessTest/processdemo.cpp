#include "processdemo.h"
#include <iostream>
using namespace std;

ProcessDemo::ProcessDemo()
{
    process = make_unique<QProcess>();
}

void ProcessDemo::start() {
    connect(process.get(),
            &QProcess::readyReadStandardOutput,
            this,
            [&]() {

    });

    connect(process.get(),
             &QProcess::readyReadStandardError,
             this,[=](){

         QString log = process->readAllStandardError();
         cout<<log.toStdString()<<endl;

    });

    QStringList argunments;
    argunments <<"123456";
    QString processPath("/Applications/Charles.app");
    process->start(processPath);

    if(process->waitForStarted(30000)) {
        cout<<"charles 启动成功"<<endl;
    } else {
        cout<<"charles 启动失败"<<endl;
    }
}
