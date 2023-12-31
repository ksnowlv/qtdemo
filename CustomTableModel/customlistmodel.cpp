#include "customlistmodel.h"

static const int KLoopMaxNumber = 50;

static const int KMaxShowNumber = 200;

CustomListModel::CustomListModel(QObject *parent)
    : QAbstractListModel{parent}
{
    m_pData = std::make_unique<QStringList>();

    for(int i = 0; i < KLoopMaxNumber; ++i) {
        const QString& res = "列表项" + QString::number(i + 1);
        m_pData->append(res);
    }
}


int CustomListModel::rowCount(const QModelIndex &parent) const
{
    return m_pData->size();
}

QVariant CustomListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        return m_pData->at(index.row());
    }

    return QVariant();
}

void CustomListModel::loadMoreData()
{
    // 模拟网络请求或其他耗时操作
    qDebug() << "Loading more data...";

    int rows = rowCount();
    int rowCount = 0;

    if (rows >= KMaxShowNumber) {
         qDebug() << "no more data...";
        return;
    } else if (rows + 5 < KMaxShowNumber ) {
        rowCount = 5;
    } else {
        rowCount = KMaxShowNumber - rows;
    }

    beginInsertRows(QModelIndex(), rows, rows + rowCount - 1);
    for (int i = 0; i < rowCount; ++i) {
        m_pData->append("列表项" + QString::number(rows + i + 1));
    }
    endInsertRows();
}

void CustomListModel::loadMoreDataFromTop()
{
    // 模拟网络请求或其他耗时操作
    qDebug() << "Loading more data from top...";

    m_pData->clear();
    for(int i = 0; i < KLoopMaxNumber; ++i) {
        const QString& res = "列表项" + QString::number(i + 1);
        m_pData->append(res);
    }
    // 通知视图进行数据更新
    emit layoutChanged();
}

