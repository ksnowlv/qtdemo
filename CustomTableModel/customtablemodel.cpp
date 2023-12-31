#include "customtablemodel.h"

#include <QDebug>

CustomTableModel::CustomTableModel(QObject *parent)
    : QAbstractTableModel{parent}
{
    m_pHeader = std::make_unique<QStringList>();

    m_pHeader->append("姓名");
    m_pHeader->append("地址");
    m_pHeader->append("年龄");
    m_pHeader->append("性别");

    m_pData = std::make_unique<QVector<QVector<QString>>>();

    const int KLoopMaxNumber = 100;

    for (int i = 0; i < KLoopMaxNumber; ++i) {
        QString name = "小明" + QString::number(i + 1);
        QString address = "地址" + QString::number(i + 1);
        QString age = QString::number(i + 1);
        QString sex = i % 2 == 0? "男":"女";
        const QVector<QString> &v = QVector<QString>{name, address, age, sex};
        m_pData->append(v);
    }
}

int CustomTableModel::rowCount(const QModelIndex &parent) const {
     Q_UNUSED(parent);

    if (m_pData == nullptr) {
        return 0;
    }

    return m_pData->size();
}

int CustomTableModel::columnCount(const QModelIndex &parent) const {
     Q_UNUSED(parent);

    if (m_pHeader == nullptr) {
        return 0;
    }

    return m_pHeader->size();
}

QVariant CustomTableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        const QString &res = m_pData->at(index.row())[index.column()];
        qDebug() << res;
        return m_pData->at(index.row())[index.column()];
    }

    return QVariant();
}

QVariant CustomTableModel::headerData(int section, Qt::Orientation orientation,
                                      int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return m_pHeader->at(section);
    }

    return QVariant();
}
