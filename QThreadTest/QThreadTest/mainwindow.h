#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class ThreadControlObject;
class ConsumerThread;
class ProducterThread;
class QWaitConditionThread;
class QWaitCondition;
class QEventLoop;
class ThreadPoolTest;

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void handleStartThread();
    void handleStopThread();
    void handleConcurrent();
    void handleConsumerProductor();
    void handleWaitConditionThread();
    void handleWaitConditionWake();
    void handleThreadPool();

private:
    void stopWaitConditionThread();

private:
    Ui::MainWindow *ui;
    unique_ptr<ThreadControlObject> threadControlObject;
    unique_ptr<ProducterThread> producterThread;
    unique_ptr<ConsumerThread> consumerThread;
    unique_ptr<QWaitConditionThread[]> waitConditionThreads;
     unique_ptr<QEventLoop[]> eventLoops;
    shared_ptr<QWaitCondition> waitCondition;
    unique_ptr<ThreadPoolTest> poolTest;

};
#endif // MAINWINDOW_H
