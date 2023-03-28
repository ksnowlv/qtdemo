#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>

#include <qlistwidget.h>
#include <QStackedWidget.h>
#include <qtablewidget.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <QHBoxLayout>
#include <qpushbutton.h>
#include <qwidget.h>
#include <qradiobutton.h>
#include <qcheckbox.h>
#include <qmenu.h>
#include <qmessagebox.h>
#include <qtablewidget.h>
#include <qtreewidget.h>

#include "person.h"
#include "provinceinfo.h"
#include "cityinfo.h"


using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , stackedContainerWidget(nullptr)
    , listContainerWidget(nullptr)
    , treeContainerWidget(nullptr)
    , tableContainerWidget(nullptr)
    , groupBoxContainerWidget(nullptr)
    , tabContainerWidget(nullptr)

{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete stackedContainerWidget;
    delete listContainerWidget;
    delete treeContainerWidget;
    delete tableContainerWidget;
    delete groupBoxContainerWidget;
    delete tabContainerWidget;
}

void MainWindow::button_stackedwidget_clicked() {
    cout<<"button_stackedwidget_clicked"<<endl;
    showStackedWidget();
}

void MainWindow::button_listwidget_clicked() {
    cout<<"button_listwidget_clicked"<<endl;
    showListWidget();
}

void MainWindow::button_treewidget_clicked() {
     cout<<"button_treewidget_clicked"<<endl;
     showTreeWidget();
}

void MainWindow::button_tablewidget_clicked() {
     cout<<"button_tablewidget_clicked"<<endl;
     showTableWidget();
}

void MainWindow::button_groupbox_clicked() {
     cout<<"button_groupbox_clicked"<<endl;
    showGroupBoxContainerWidget();
}

void MainWindow::button_tabwidget_clicked() {
     cout<<"button_tabwidget_clicked"<<endl;
    showTabWidget();
}

void MainWindow::initStackedWidget() {

    QHBoxLayout* mainLayout = new QHBoxLayout();

    stackedContainerWidget = new QWidget();
    stackedContainerWidget->setLayout(mainLayout);
    stackedContainerWidget->setGeometry(this->geometry());

    QPushButton* button = new QPushButton();
    button->setText("退出");
    connect(button,
            &QPushButton::clicked,
            this,
            [&]() {
                stackedContainerWidget->hide();
                this->show();}
    );

    mainLayout->addWidget(button,1,Qt::AlignRight);

}

void MainWindow::showStackedWidget() {
    if(nullptr == stackedContainerWidget) {
        initStackedWidget();
    }

    stackedContainerWidget->show();
    this->hide();
}

void MainWindow::initListWidget() {

    QVBoxLayout* mainLayout = new QVBoxLayout();

    listContainerWidget = new QWidget();
    listContainerWidget->setLayout(mainLayout);
    listContainerWidget->setGeometry(this->geometry());
    listContainerWidget->setWindowTitle("QStackedWidget控件&QStackedWidget");

    QPushButton* button = new QPushButton();
    button->setText("退出");
    connect(button,
            &QPushButton::clicked,
            this,
            [&]() {
                listContainerWidget->hide();
                this->show();}
    );

    mainLayout->addWidget(button,1,Qt::AlignRight);

    QHBoxLayout* hBoxlayout = new QHBoxLayout();
    mainLayout->addLayout(hBoxlayout);

    QListWidget* listWidget = new QListWidget();
    QStackedWidget* stackedWidget = new QStackedWidget();
    QVector<QString> stringVector{"窗口选项1","窗口选项2", "窗口选项3", "窗口选项4","窗口选项5"};
    QVector<QString> vector{"窗口1","窗口2", "窗口3", "窗口4","窗口5"};

    for (int i = 0; i < stringVector.count(); ++i) {
        listWidget->addItem(stringVector[i]);

        QWidget* subWidget = new QWidget();
        QVBoxLayout* subWidgetMainLayout = new QVBoxLayout();
        subWidget->setLayout(subWidgetMainLayout);

        QLabel* label = new QLabel(vector[i]);
        label->setStyleSheet("background-color:#ff00ff;");
        label->setText(vector[i]);
        subWidgetMainLayout->addWidget(label,1, Qt::AlignTop);

        stackedWidget->addWidget(subWidget);
    }

    //设置主窗口布局
    hBoxlayout->addWidget(listWidget);
    hBoxlayout->addWidget(stackedWidget);
    hBoxlayout->setStretchFactor(listWidget,1);
    hBoxlayout->setStretchFactor(stackedWidget, 5);

    connect(listWidget,
            &QListWidget::currentRowChanged,
            stackedWidget,
            &QStackedWidget::setCurrentIndex);
}

void MainWindow::showListWidget() {
    if(nullptr == listContainerWidget) {
        initListWidget();
    }

    listContainerWidget->show();
    this->hide();
}

void MainWindow::initTreeWidget() {
    QVBoxLayout* mainLayout = new QVBoxLayout();

    treeContainerWidget = new QWidget();
    treeContainerWidget->setLayout(mainLayout);
    treeContainerWidget->setGeometry(this->geometry());

    QPushButton* button = new QPushButton();
    button->setText("退出");
    connect(button,
            &QPushButton::clicked,
            this,
            [&]() {
                treeContainerWidget->hide();
                this->show();}
    );

    mainLayout->addWidget(button, 1 ,Qt::AlignRight);

    QTreeWidget* treeWidget = new QTreeWidget();
    mainLayout->addWidget(treeWidget,6, Qt::AlignHCenter);
    treeWidget->setHeaderLabel("省份");
    treeWidget->setMinimumWidth(350);

    QVector<ProvinceInfo*> provinceInfoVector;

    QVector<QString> cityVector{"北京", "天津", "上海", "重庆"};

    foreach (const QString& city, cityVector) {
        ProvinceInfo* provinceInfo = new ProvinceInfo();
        provinceInfo->setProvinceName(city);
        provinceInfo->append(CityInfo(city));
        provinceInfoVector.append(provinceInfo);
    }

    for (int i = 0; i < cityVector.count(); ++i) {
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0, cityVector[i]);
        treeWidget->addTopLevelItem(item);
        item->setCheckState(0,Qt::Unchecked);

        QTreeWidgetItem* subItem = new QTreeWidgetItem(item);
        subItem->setText(0, cityVector[i]);
        treeWidget->addTopLevelItem(subItem);
        subItem->setCheckState(0,Qt::Unchecked);
    }

    ProvinceInfo* provinceInfo = new ProvinceInfo();
    provinceInfo->setProvinceName("河南");

    QVector<QString> HNCityVector{"郑州", "新乡", "焦作", "洛阳", "安阳" ,"洛阳", "周口", "平顶山", "驻马店"};

    foreach (const QString& city, HNCityVector) {
        provinceInfo->append(CityInfo(city));
    }

    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0, provinceInfo->getProvinceName());
    treeWidget->addTopLevelItem(item);
    item->setCheckState(0,Qt::Checked);

    foreach (const CityInfo& cityInfo, provinceInfo->getCityInfoVector()) {
        QTreeWidgetItem* subItem = new QTreeWidgetItem(item);
        subItem->setText(0, cityInfo.getCityName());
        treeWidget->addTopLevelItem(subItem);
        subItem->setCheckState(0,Qt::Checked);

        for(int i = 0; i < 5; ++i) {
            QTreeWidgetItem* childItem = new QTreeWidgetItem(subItem);
            childItem->setText(0, "区县 " + QString::number(i+1));
            treeWidget->addTopLevelItem(childItem);
            childItem->setCheckState(0,Qt::Checked);
        }
    }
}

void MainWindow::showTreeWidget() {
    if(nullptr == treeContainerWidget) {
        initTreeWidget();
    }

    treeContainerWidget->show();
    this->hide();
}

void MainWindow::initTableWidget() {
    QVBoxLayout* mainLayout = new QVBoxLayout();

    tableContainerWidget = new QWidget();
    tableContainerWidget->setLayout(mainLayout);
    tableContainerWidget->setGeometry(this->geometry());
    tableContainerWidget->setWindowTitle("QTableWidget控件");

    QPushButton* button = new QPushButton();
    button->setText("退出");
    connect(button,
            &QPushButton::clicked,
            this,
            [&]() {
                tableContainerWidget->hide();
                this->show();}
    );

    mainLayout->addWidget(button,1,Qt::AlignRight);

    QTableWidget* tableWidget = new QTableWidget();
    mainLayout->addWidget(tableWidget);
    QVector<Person> persons;

    for (int i = 0; i < 10; ++i) {
        Person* person = new Person();
        person->setName("tom " + QString::number(i + 1));
        person->setAddress("北京海淀区友谊路唐家岭新城东区 " + QString::number(i + 1));
        person->setPhone("1512345678"+ QString::number(i));
        person->setAge(i+1);
        persons.append(*person);
    }

    tableWidget->setColumnCount(4);
    tableWidget->setRowCount(persons.count());
    tableWidget->setHorizontalHeaderLabels(QStringList() << "姓名" << "地址" << "手机号" << "年龄");
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);


    for(int i = 0; i < persons.count(); ++i) {

        QTableWidgetItem* firstItem = new QTableWidgetItem();
        firstItem->setText(persons[i].getName());

        QTableWidgetItem* secondItem = new QTableWidgetItem();
        secondItem->setText(persons[i].getAddress());

        QTableWidgetItem* thirdItem = new QTableWidgetItem();
        thirdItem->setText(persons[i].getPhone());

        QTableWidgetItem* fourthItem = new QTableWidgetItem();
        fourthItem->setText(QString::number(persons[i].getAge()));

        tableWidget->setItem(i,0, firstItem);
        tableWidget->setItem(i,1, secondItem);
        tableWidget->setItem(i,2, thirdItem);
        tableWidget->setItem(i,3, fourthItem);
        tableWidget->setRowHeight(i, 40);
    }

    tableWidget->setColumnWidth(0, 80);
    tableWidget->setColumnWidth(1, 230);
    tableWidget->setColumnWidth(2, 120);
    tableWidget->setColumnWidth(3, 50);
}

void MainWindow::showTableWidget() {

    if(nullptr == tableContainerWidget) {
        initTableWidget();
    }

    tableContainerWidget->show();
    this->hide();
}

void MainWindow::initGroupBoxContainerWidget() {
    QVBoxLayout* mainLayout = new QVBoxLayout();

    groupBoxContainerWidget = new QWidget();
    groupBoxContainerWidget->setLayout(mainLayout);
    groupBoxContainerWidget->setGeometry(this->geometry());
    groupBoxContainerWidget->setWindowTitle("QGroupBox控件");

    QPushButton* button = new QPushButton();
    button->setText("退出");
    connect(button,
            &QPushButton::clicked,
            this,
            [&]() {
                groupBoxContainerWidget->hide();
                this->show();}
    );

    mainLayout->addWidget(button,1,Qt::AlignRight);

    //
    QGroupBox* firstBox = new QGroupBox("单选按钮组");
    QVector<QString> firstRadios{"单选按钮1", "单选按钮2", "单选按钮3", "单选按钮4", "单选按钮5"};

    QVBoxLayout* firstVBoxLayout = new QVBoxLayout();
    firstBox->setLayout(firstVBoxLayout);

    for (int i = 0; i < firstRadios.count(); ++i) {
        QRadioButton* button = new QRadioButton(firstRadios[i]);
        firstVBoxLayout->addWidget(button);
    }

    mainLayout->addWidget(firstBox);

    //
    QGroupBox* secondBox = new QGroupBox("单选按钮组");
    QVector<QString> secondRadios{"多选按钮1", "多选按钮2", "多选按钮3", "多选按钮4", "多选按钮5"};

    QVBoxLayout* secondVBoxLayout = new QVBoxLayout();
    secondBox->setLayout(secondVBoxLayout);

    for (int i = 0; i < secondRadios.count(); ++i) {
        QCheckBox* button = new QCheckBox(firstRadios[i]);
        secondVBoxLayout->addWidget(button);
    }

    mainLayout->addWidget(secondBox);
    QGroupBox* thirdBox = new QGroupBox("可选普通按钮组");
    thirdBox->setCheckable(true);
    thirdBox->setChecked(true);

    QVBoxLayout* thirdVBoxLayout = new QVBoxLayout();
    thirdBox->setLayout(thirdVBoxLayout);

    QPushButton* pushButton1 = new QPushButton("普通按钮1");
    pushButton1->setCheckable(true);
    pushButton1->setChecked(true);

    QPushButton* pushButton2 = new QPushButton("普通按钮2");
    QVector<QString> menuVector{"菜单1", "菜单2", "菜单3", "菜单4", "菜单5"};
    QMenu* menu  = new QMenu(this);
    menu->addSeparator();

    menu->setStyleSheet(
                         "\
                         QMenu {\
                         background-color:rgb(255,87,87); /*整个背景*/\
                         border: 3px solid rgb(235,110,110);/*整个菜单边缘*/\
                         }\
                     QMenu::item {\
                         font-size: 10pt; \
                         color: rgb(225,225,225);  /*字体颜色*/\
                         border: 3px solid rgb(60,60,60);    /*item选框*/\
                         background-color:rgb(89,87,87);\
                         padding:16px 16px; /*设置菜单项文字上下和左右的内边距，效果就是菜单中的条目左右上下有了间隔*/\
                         margin:2px 2px;/*设置菜单项的外边距*/\
                          }\
                     QMenu::item:selected { \
                         background-color:rgb(235,110,36);/*选中的样式*/\
                         }\
                     QMenu::item:pressed {/*菜单项按下效果*/\
                                               border: 1px solid rgb(60,60,61); \
                                               background-color: rgb(220,80,6); \
                                           }");

    foreach (const QString& str, menuVector) {
      QAction* action =  menu->addAction(str);
      connect(action,
              &QAction::triggered,
              this,
              [=]() {

            cout<<str.toStdString()<<"被点击"<<endl;
            pushButton2->setText(str);
            QMessageBox::StandardButton button = QMessageBox::information(this, "消息框", "你点击了"+ str,
                                        QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::NoButton);

            if(button == QMessageBox::Yes) {
                cout<<"QMessageBox::Yes 被点击"<<endl;
            } else if(button == QMessageBox::Cancel) {
                cout<<"QMessageBox::Cancel 被点击"<<endl;
            }
      });
    }
    pushButton2->setMenu(menu);

    QPushButton* pushButton3 = new QPushButton("普通按钮3");
    pushButton3->setFlat(true);

    thirdVBoxLayout->addWidget(pushButton1, 1, Qt::AlignLeft);
    thirdVBoxLayout->addWidget(pushButton2, 1, Qt::AlignLeft);
    thirdVBoxLayout->addWidget(pushButton3, 1, Qt::AlignLeft);

    mainLayout->addWidget(thirdBox);
}

void MainWindow::showGroupBoxContainerWidget() {
    if(nullptr == groupBoxContainerWidget) {
        initGroupBoxContainerWidget();
    }

    groupBoxContainerWidget->show();
    this->hide();
}

void MainWindow::initTabWidget() {

    QVBoxLayout* mainLayout = new QVBoxLayout();

    tabContainerWidget = new QWidget();
    tabContainerWidget->setLayout(mainLayout);
    tabContainerWidget->setGeometry(this->geometry());
    tabContainerWidget->setWindowTitle("QTabWidget控件");

    QPushButton* button = new QPushButton();
    button->setText("退出");
    connect(button,
            &QPushButton::clicked,
            this,
            [&]() {
                tabContainerWidget->hide();
                this->show();}
    );

    mainLayout->addWidget(button,1,Qt::AlignRight);

    QTabWidget* tabWidget = new QTabWidget();
    mainLayout->addWidget(tabWidget);

    QVector<QString> tabNames{"窗口选项1", "窗口选项2", "窗口选项3", "窗口选项4", "窗口选项5"};

    for (int i = 0; i < tabNames.count(); ++i) {

        QWidget *subWidget = new QWidget();
        subWidget->setStyleSheet("background-color:#ff00ff;");
        tabWidget->addTab(subWidget, tabNames[i]);
        QVBoxLayout* subMainLayout = new QVBoxLayout();
        subWidget->setLayout(subMainLayout);

        QLabel* label = new QLabel();
        label->setText(tabNames[i]);
        subMainLayout->addWidget(label, 0, Qt::AlignCenter);

        QPushButton* button = new QPushButton();
        button->setText(tabNames[i]);
        subMainLayout->addWidget(button);
    }
}

void MainWindow::showTabWidget() {
    if(nullptr == tabContainerWidget) {
        initTabWidget();
    }

    tabContainerWidget->show();
    this->hide();
}
