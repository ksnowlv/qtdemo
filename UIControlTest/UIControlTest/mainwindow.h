#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QListWidget;

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

    void initStackedWidget();
    void showStackedWidget();

    void initListWidget();
    void showListWidget();

    void initTreeWidget();
    void showTreeWidget();

    void initTableWidget();
    void showTableWidget();

    void initGroupBoxContainerWidget();
    void showGroupBoxContainerWidget();

private:
    Ui::MainWindow *ui;

    QWidget* stackedContainerWidget;
    QWidget* listContainerWidget;
    QWidget* treeContainerWidget;
    QWidget* tableContainerWidget;
    QWidget* groupBoxContainerWidget;


};
#endif // MAINWINDOW_H
