#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QtPdf/qpdfpagenavigator.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class QTimer;
class QPdfPageSelector;
class QPdfView;
class QPdfDocument;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleShowPdfEvent();
    void handleSavePdfEvent();

private:
    void initPDF();
    void pageSelected(int page);

private:
    Ui::MainWindow *ui;
    QList<QPixmap> imageList;
    QPdfPageSelector *m_pageSelector;
    QPdfView *m_pdfView;
    QPdfDocument* m_pdfDocument;
};
#endif // MAINWINDOW_H
