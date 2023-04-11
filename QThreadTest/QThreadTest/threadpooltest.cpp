#include "threadpooltest.h"
#include <iostream>
using namespace std;

const int RunnableTasksNum = 5;

ThreadPoolTest::ThreadPoolTest(QObject *parent)
    : QObject{parent}
{
    pool = make_unique<QThreadPool>();
    pool->setMaxThreadCount(2);

    runnableTasks = new ThreadRunnable[RunnableTasksNum];

    for (int i = 0; i < RunnableTasksNum; ++i) {
        connect(&runnableTasks[i],
                &ThreadRunnable::completeEvent,
                this,
                [](const int type) {
               //cout<<"type:"<<QString::number(type).toStdString()<<endl;
        });
        connect(this,
                &ThreadPoolTest::sendMessageToThread,
                &runnableTasks[i],
                &ThreadRunnable::revMessageFromMain);
    }

}

ThreadPoolTest::~ThreadPoolTest() {

    if(nullptr == runnableTasks) {
        delete[] runnableTasks;
        runnableTasks = nullptr;
    }
}


void ThreadPoolTest::startTask() {

    for (int i = 0; i < RunnableTasksNum; ++i) {
        ThreadRunnable* threadRunnable= new ThreadRunnable(this);
         pool->start(threadRunnable);
       //设置不自动删除
       threadRunnable->setAutoDelete(true);
       emit sendMessageToThread("thread start" + QString::number(i + 1));
    }

    return;


    for (int i = 0; i < RunnableTasksNum; ++i) {
       pool->start(&runnableTasks[i]);
       //设置不自动删除
       runnableTasks[i].setAutoDelete(false);
       emit sendMessageToThread("thread start" + QString::number(i + 1));
    }
}
