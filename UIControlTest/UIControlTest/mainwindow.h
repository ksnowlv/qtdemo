#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QListWidget;
class QHBoxLayout;

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void button_stackedwidget_clicked();
    void button_listwidget_clicked();
    void button_treewidget_clicked();
    void button_tablewidget_clicked();
    void button_groupbox_clicked();

private:
    void initListWidget();
    void showListWidget();
private:
    Ui::MainWindow *ui;

    QWidget* listContainerWidget;

};
#endif // MAINWINDOW_H
