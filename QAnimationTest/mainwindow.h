#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <qpropertyanimation.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}


QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handlePropertyAnimationEvent();
    void handleParallelAnimationGroupEvent();
    void handleSequentialAnimationGroupEvent();


private:
    Ui::MainWindow *ui;

private:
    QPushButton *animationButton; // 按钮成员变量
};
#endif // MAINWINDOW_H
