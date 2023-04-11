#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "threadcontrolobject.h"
#include <iostream>
#include <QSemaphore>
#include <QWaitCondition>
#include <QThreadPool>
#include "consumerthread.h"
#include "producterthread.h"
#include "qwaitconditionthread.h"
#include "threadpooltest.h"


using namespace std;

const int WaitConditionThreadNumber = 6;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    threadControlObject = make_unique<ThreadControlObject>();
    connect(threadControlObject.get(),
            &ThreadControlObject::workerResult,
            this,
            [&](const QString& message) {
        cout<<"****"<<__func__<<this_thread::get_id()<<endl;
        ui->showInfomationLabel->setText(message);
    });
    cout<<"main thread"<<this_thread::get_id()<<endl;

    //waitcondition
    waitConditionThreads = make_unique<QWaitConditionThread[]>(WaitConditionThreadNumber);
    eventLoops = make_unique<QEventLoop[]>(WaitConditionThreadNumber);

    waitCondition = make_shared<QWaitCondition>();

    //threadpool
    poolTest = make_unique<ThreadPoolTest>();
}

MainWindow::~MainWindow()
{
    delete ui;

    if(threadControlObject) {
        threadControlObject->threadStop();
    }


    if(producterThread) {
        producterThread->exit();
    }

    if(consumerThread) {
        consumerThread->exit();
    }


    stopWaitConditionThread();
}

void MainWindow::handleStartThread() {

    threadControlObject->threadStart();
}

void MainWindow::handleStopThread() {
    threadControlObject->threadStop();
}

void MainWindow::handleConcurrent() {
    threadControlObject->concurrentStart();
}

void MainWindow::handleConsumerProductor() {

    if(producterThread) {
        producterThread->exit();
    }

    if(consumerThread) {
        consumerThread->exit();
    }

    shared_ptr<QSemaphore> producterSemaphore = make_shared<QSemaphore>(1);
    shared_ptr<QSemaphore> consumerSemaphore = make_shared<QSemaphore>(0);

    producterThread = make_unique<ProducterThread>();
    consumerThread = make_unique<ConsumerThread>();
    producterThread->setSemaphore(producterSemaphore, consumerSemaphore);
    consumerThread->setSemaphore(producterSemaphore, consumerSemaphore);

    connect(producterThread.get(), &QThread::finished, producterThread.get(), &QThread::deleteLater);
    connect(consumerThread.get(), &QThread::finished, consumerThread.get(), &QThread::deleteLater);

    producterThread->start();
    consumerThread->start();
}

void MainWindow::handleWaitConditionThread() {

    for (int i = 0; i < WaitConditionThreadNumber; ++i) {
        waitConditionThreads[i].setWaitCondition(waitCondition);
        waitConditionThreads[i].start();
        /*cout<<"----1"<<endl;
        connect(&waitConditionThreads[i],SIGNAL(finished()),&eventLoops[i],SLOT(quit()))*/;
    }
}

void MainWindow::handleWaitConditionWake() {
    waitCondition->wakeAll();
    cout<<"wakeAll"<<endl;
}

void MainWindow::stopWaitConditionThread() {

    if( nullptr != waitConditionThreads) {
        for (int i = 0; i < WaitConditionThreadNumber; ++i) {
            waitConditionThreads[i].setExitFlag(true);
        }
    }

    if(nullptr != waitCondition) {
        waitCondition->wakeAll();
    }

    if( nullptr != waitConditionThreads) {
        for (int i = 0; i < WaitConditionThreadNumber; ++i) {
            waitConditionThreads[i].requestInterruption();
            waitConditionThreads[i].quit();
            waitConditionThreads[i].wait();
        }
    }
}

void MainWindow::handleThreadPool() {
    poolTest->startTask();
}

