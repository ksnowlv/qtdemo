#ifndef CUSTOMLISTMODEL_H
#define CUSTOMLISTMODEL_H


#include <QAbstractListModel>
#include <QStringList>
#include <QStyledItemDelegate>
#include <QPainter>

class MyListViewItemDelegate : public QStyledItemDelegate
{
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        if(!index.isValid()) {
            return;
        }

        QStyledItemDelegate::paint(painter, option, index);

        // 绘制分隔线
        if (index.row() < index.model()->rowCount() - 1) {
            painter->setPen(Qt::lightGray);
            painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
        }
    }

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        if (!index.isValid()) {
            return QSize(0, 0);
        }

        QSize size = QStyledItemDelegate::sizeHint(option, index);
        // 设置每个列表项的高度为 50
        size.setHeight(50);
        return size;
    }
};

class CustomListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CustomListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // 上拉加载更多数据
    void loadMoreData();
    // 下拉加载更多数据
    void loadMoreDataFromTop();

private:
    std::unique_ptr<QStringList> m_pData;
};

#endif // CUSTOMLISTMODEL_H
