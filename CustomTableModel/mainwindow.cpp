#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "customtablemodel.h"
#include "customlistmodel.h"
#include "customitemmodel.h"
#include <qscrollbar.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    CustomTableModel *tableModel = new CustomTableModel(this);
    ui->tableView->setModel(tableModel);

    initListView();
    initTreeView();
}

void MainWindow::initListView() {
    CustomListModel *listModel = new CustomListModel(this);
    QListView *listView = ui->listView;
    listView->setModel(listModel);
    listView->setItemDelegate(new MyListViewItemDelegate);

    // 设置背景
    listView->setStyleSheet("background-color: yellow;");

    listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QObject::connect(listView->verticalScrollBar(), &QScrollBar::valueChanged, [listView, listModel](int value) {
        QScrollBar *scrollBar = listView->verticalScrollBar();
        int max = scrollBar->maximum();
        int min = scrollBar->minimum();
        qDebug()<<"max:"<<max<<","<<"min:"<<min;
        if (value == max) {
            listModel->loadMoreData();
        }
        else if (value == min) {
            listModel->loadMoreDataFromTop();
        }
    });
}

void MainWindow::initTreeView() {
    // 创建数据项节点
    MyItemNode *root = new MyItemNode("Root");
    MyItemNode *node1 = new MyItemNode("Node 1", root);
    MyItemNode *node2 = new MyItemNode("Node 2", root);
    MyItemNode *node3 = new MyItemNode("Node 3", node2);
    MyItemNode *node4 = new MyItemNode("Node 4", node2);
    MyItemNode *node5 = new MyItemNode("Node 5", node4);

    // 组织树结构
    root->addChild(node1);
    root->addChild(node2);
    node2->addChild(node3);
    node2->addChild(node4);
    node4->addChild(node5);

    CustomItemModel *itemModel = new CustomItemModel(this);
    itemModel->setRootNode(root);
    ui->treeView->setModel(itemModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}
