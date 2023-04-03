#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class ThreadControlObject;
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

private:
    Ui::MainWindow *ui;
    unique_ptr<ThreadControlObject> threadControlObject;
};
#endif // MAINWINDOW_H
