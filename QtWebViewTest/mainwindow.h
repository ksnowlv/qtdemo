#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class QWebEngineView;
class QWebChannel;
class MyObject;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleNativeCallWebPushButtonClicked();

    void handleWebCallNativePushButtonClicked();

private:
    Ui::MainWindow *ui;
    QWebEngineView *webEngineView;
    std::unique_ptr<QWebChannel> webChannel;
    std::unique_ptr<MyObject> myObject;
};
#endif // MAINWINDOW_H
