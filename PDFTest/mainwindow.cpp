#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPdfDocument>
#include <QThread>
#include <QTimer>
#include <QListWidgetItem>
#include <QListWidget>
#include <QFileDialog>
#include <QtPdfWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // // 创建定时器
    // timer = new QTimer(this);
    // count = 0;
    // // 每次定时器超时触发的槽函数
    // connect(timer, &QTimer::timeout, this, [&]() {
    //     if (count < imageList.count()) {
    //         ui->label->setPixmap(imageList.at(count));
    //     }

    //     ++count;
    //     qDebug()<<count<<",image count"<<imageList.count();
    // });

    initPDF();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::handleShowPdfEvent() {
    QString filePath = ":/resource/k8s 实战案例.pdf";
    QPdfDocument pdfDoc(this);
    const QPdfDocument::Error& error = pdfDoc.load(filePath);

    if (error != QPdfDocument::Error::None) {
        qDebug()<<"pdf open error";
        return;
    }

    imageList.clear();

    for (int page = 0; page < pdfDoc.pageCount(); page++)
    {
        QSizeF size = pdfDoc.pagePointSize(page);
        QImage image = pdfDoc.render(page, QSize(size.width(), size.height()));
        QPixmap pixmap = QPixmap::fromImage(image);
        imageList.append(pixmap);
    }

    pdfDoc.close();

    // timer->start(1000);

    QListWidget* listWidget = ui->listWidget;

    // 添加图片文件名和图像到列表中
    for (const QPixmap& pixmap : imageList) {
        // 添加图片文件名
        QListWidgetItem *item = new QListWidgetItem(listWidget, 0);
        item->setIcon(QIcon(pixmap.scaled(listWidget->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));

        item->setTextAlignment(Qt::AlignHCenter); // 设置文本居中显示
        listWidget->addItem(item);
    }

    listWidget->setIconSize(listWidget->size());
}

void MainWindow::handleSavePdfEvent() {

    // 获取目标目录
    QString saveDir = QFileDialog::getExistingDirectory(nullptr, "选择保存目录", QDir::homePath());

    int countImage = 0;
    for(const QPixmap& pixmap : imageList) {
        QString fileName = saveDir+ QString("/page_%1.png").arg(countImage);
        bool ok = pixmap.save(fileName);
        qDebug()<<fileName<< ",ok:"<<ok;
        ++countImage;
    }
}

void MainWindow::initPDF() {
    // 创建 QPdfPageSelector 控件
    m_pageSelector = new QPdfPageSelector(this);
    m_pageSelector->setGeometry(310,0,30,600);

    // 创建 QPdfView 控件
    m_pdfView = new QPdfView(this);
    m_pdfView->setGeometry(0,0, 300, 600);

    QString filePath = ":/resource/k8s 实战案例.pdf";
    m_pdfDocument = new QPdfDocument(this);
    const QPdfDocument::Error& error = m_pdfDocument->load(filePath);

    m_pdfView->setDocument(m_pdfDocument);
    m_pdfView->setPageMode(QPdfView::PageMode::MultiPage);

    m_pageSelector->setDocument(m_pdfDocument);
    connect(m_pageSelector, &QPdfPageSelector::currentPageChanged, this, &MainWindow::pageSelected);
    m_pageSelector->setMaximumWidth(150);
}

void MainWindow::pageSelected(int page)
{
    auto pageNavigator = m_pdfView->pageNavigator();
    pageNavigator->jump(page, {}, pageNavigator->currentZoom());
    const auto documentTitle = m_pdfDocument->metaData(QPdfDocument::MetaDataField::Title).toString();
    setWindowTitle(!documentTitle.isEmpty() ? documentTitle : QStringLiteral("PDF Viewer"));
    setWindowTitle(tr("%1: page %2 (%3 of %4)")
                       .arg(documentTitle.isEmpty() ? u"PDF Viewer"_qs : documentTitle,
                            m_pageSelector->currentPageLabel(), QString::number(page + 1), QString::number(m_pdfDocument->pageCount())));
}
