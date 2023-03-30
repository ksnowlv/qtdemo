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
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;

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

    stackedContainerWidget = make_unique<QWidget>();
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

    listContainerWidget = make_unique<QWidget>();
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

    treeContainerWidget = make_unique<QWidget>();;
    treeContainerWidget->setLayout(mainLayout);
    treeContainerWidget->setGeometry(this->geometry());
    treeContainerWidget->setWindowTitle("QTreeWidget控件");

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
    treeWidget->setHeaderLabels({"省份", "描述"});
    treeWidget->setMinimumWidth(500);
    treeWidget->setColumnWidth(0, 170);
    treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(treeWidget,
            &QTreeWidget::itemClicked,
            this,
            [=](QTreeWidgetItem* item, int count) {
            cout<<"item text:"
               <<item->text(0).toStdString()
               <<endl;
        });

    QMenu* treeWidgetMenu = new QMenu(treeWidget);
    QAction* copyAction = treeWidgetMenu->addAction("拷贝");
    connect(copyAction,
            &QAction::triggered,
            this,
            [=]() {

          cout<<"拷贝被点击"<<endl;

          QMessageBox::StandardButton button = QMessageBox::information(this, "消息框", "文本已复制!!!",
                                      QMessageBox::Ok,QMessageBox::NoButton);

          if(button == QMessageBox::Ok) {
              cout<<"QMessageBox::Ok 被点击"<<endl;
          }
    });

    treeWidgetMenu->addAction("删除");

    connect(treeWidget,
            &QTreeWidget::customContextMenuRequested,
            this,
            [=](const QPoint &pos){
        treeWidgetMenu->exec(treeWidget->mapToGlobal(pos));
    });

    QVector<ProvinceInfo*> provinceInfoVector;

    QVector<QString> cityVector{"北京", "天津", "上海", "重庆"};
    QVector<QString> cityDescritipnVector{"北京（Beijing），简称“京”，古称燕京、北平，是中华人民共和国首都、直辖市、国家中心城市、超大城市，国务院批复确定的中国政治中心、文化中心、国际交往中心、科技创新中心， [1]  中国历史文化名城和古都之一。 [145]  截至2020年，北京市下辖16个区，总面积16410.54平方千米。 [83]  2022年末，北京市常住人口2184.3万人",
                                          "天津市，简称“津”，别称津沽、津门，是中华人民共和国省级行政区、直辖市、国家中心城市、超大城市，全国先进制造研发基地、北方国际航运核心区、金融创新运营示范区、改革开放先行区。 [161]  中国北方对外开放的门户，中国北方的航运中心、物流中心和现代制造业基地 [105]  ，环渤海地区的经济中心 [1-2]  ，国际消费中心城市 [91]  和区域商贸中心城市 [162]  ，国际性综合交通枢纽 [163]  ，中国国际航空物流中心",
                                          "上海，简称“沪”或“申”，是中华人民共和国直辖市、国家中心城市、超大城市、上海大都市圈核心城市，中华人民共和国国务院批复确定的中国国际经济、金融、贸易、航运、科技创新中心，中国历史文化名城之一。 [1]  上海市总面积6340.5平方千米，辖16个区。 [5]  [182]  2022年末，上海市常住人口为2475.89万人",
                                          "重庆市，简称“渝” [4]  ，别称山城、江城，是中华人民共和国直辖市、国家中心城市、超大城市 [114]  ，国务院批复的国家重要的中心城市之一、长江上游地区经济中心 [1]  ，成渝地区双城经济圈核心城市 [159]  ，国家重要先进制造业中心、西部金融中心、西部国际综合交通枢纽和国际门户枢纽。 [140]  辖38个区县，总面积8.24万平方千米。2022年末常住人口3213.34万人"};

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
        subItem->setCheckState(0,Qt::Unchecked);
    }

    ProvinceInfo* provinceInfo = new ProvinceInfo();
    provinceInfo->setProvinceName("河南");
    provinceInfo->setProvinceDescription("河南省，简称“豫”，中华人民共和国省级行政区，省会郑州市，是全国农产品主产区和重要的矿产资源大省、人口大省、重要的综合交通枢纽和人流、物流、信息流中心、全国农业大省和粮食转化加工大省。 [111]  河南省位于中国中东部、黄河中下游，东接安徽、山东，北接河北、山西，西连陕西，南临湖北，总面积16.7万平方千米");

    QVector<QString> HNCityVector{"郑州", "新乡", "焦作", "洛阳", "安阳" ,"洛阳", "周口", "平顶山", "驻马店"};
    QVector<QString> HNCityDescriptionVector{"简称“郑”，史谓“天地之中”，古称商都，今谓绿城，河南省辖地级市、省会、 [144]  特大城市 [216]  、《促进中部地区崛起“十三五”规划》明确支持建设中的国家中心城市",
                                             "河南省辖地级市，地处河南省北部，南临黄河，与郑州、开封隔河相望；北依太行，与鹤壁、安阳毗邻；西连焦作并与山西接壤；东接油城濮阳并与山东相连，总面积8249平方千米。 [55]  截至2022年，新乡市辖4个市辖区、5个县、1个城乡一体化示范区、2个国家级开发区，代管3个县级市。 [86]  2021年，新乡市常住人口617.1万", "焦作", "洛阳", "安阳" ,"洛阳", "周口", "平顶山", "驻马店"};
    foreach (const QString& city, HNCityVector) {
        provinceInfo->append(CityInfo(city));
    }

    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0, provinceInfo->getProvinceName());
    item->setText(1, provinceInfo->getProvinceDescription());

    treeWidget->addTopLevelItem(item);
    item->setCheckState(0,Qt::Checked);

    for (int i = 0; i < HNCityVector.count(); ++i) {
        QTreeWidgetItem* subItem = new QTreeWidgetItem(item);
        subItem->setText(0, HNCityVector[i]);
        subItem->setText(1, HNCityDescriptionVector[i]);
        //subItem->setSizeHint(1, QSize(0, 100));
        subItem->setCheckState(0,Qt::Checked);

        for(int i = 0; i < 5; ++i) {
            QTreeWidgetItem* childItem = new QTreeWidgetItem(subItem);
            childItem->setText(0, "区县 " + QString::number(i+1));
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

static const QString qssTableWidgetStyle =
    "QTableWidget::item:hover"
    "{\
        background-color:rgb(92,188,227,200)"
    "}"
    "QTableWidget::item:selected"
    "{\
        background-color:#1B89A1"
    "}"
    "QHeaderView::section,QTableCornerButton:section"
    "{\
        padding:3px; margin:0px; color:#DCDCDC;  border:1px solid #242424;\
        border-left-width:0px; border-right-width:1px; border-top-width:0px; border-bottom-width:1px;\
        background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #646464,stop:1 #525252); "
    "}"
    "QTableWidget"
    "{\
        background-color:white;border:none;"
    "}";


void MainWindow::initTableWidget() {
    QVBoxLayout* mainLayout = new QVBoxLayout();

    tableContainerWidget = make_unique<QWidget>();
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
    tableWidget->setStyleSheet(qssTableWidgetStyle);
    mainLayout->addWidget(tableWidget);
    QVector<Person> persons;

    for (int i = 0; i < 50; ++i) {
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

    groupBoxContainerWidget = make_unique<QWidget>();;
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
                                        QMessageBox::Yes|QMessageBox::No,QMessageBox::NoButton);

            if(button == QMessageBox::Yes) {
                cout<<"QMessageBox::Yes 被点击"<<endl;
            } else if(button == QMessageBox::No) {
                cout<<"QMessageBox::No 被点击"<<endl;
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

    tabContainerWidget = make_unique<QWidget>();;
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

    QVector<QString> tabNames{"窗口选项1", "窗口选项2",
                              "窗口选项3", "窗口选项4",
                              "窗口选项5", "窗口选项6",
                              "窗口选项7", "窗口选项8",
                              "窗口选项9", "窗口选项10"};

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
