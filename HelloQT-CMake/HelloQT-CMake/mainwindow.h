#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; class QPushButton; class QLabel;}
QT_END_NAMESPACE

class LoginWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_HelloQTClick();

private:
    Ui::MainWindow *ui;
    Ui::QPushButton *checkButton;
    Ui::QLabel *label;
    QGridLayout *m_GridLayout;
    std::unique_ptr<LoginWindow> loginWindow;
};
#endif // MAINWINDOW_H
