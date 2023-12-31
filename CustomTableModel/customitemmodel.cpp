#include "customitemmodel.h"

CustomItemModel::CustomItemModel(QObject *parent)
    : QAbstractItemModel{parent}
{
    m_pRootNode = std::make_unique<MyItemNode>("rootNode");


    const int KLoopMaxNumber = 100;

    for (int i = 0; i < KLoopMaxNumber; ++i) {
        MyItemNode *child = new MyItemNode("child" + QString::number(i + 1), m_pRootNode.get());
        m_pRootNode->addChild(child);
    }
}


QModelIndex CustomItemModel::index(int row, int column, const QModelIndex &parent) const {
    if(!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    MyItemNode *parentNode = nodeFromIndex(parent);
    MyItemNode *childNode = parentNode->child(row);

    if (childNode) {
        return createIndex(row, column, childNode);
    } else {
        return QModelIndex();
    }
}

QModelIndex CustomItemModel::parent(const QModelIndex &index) const {
    if (!index.isValid()) {
        return QModelIndex();
    }

    MyItemNode *childNode = nodeFromIndex(index);
    MyItemNode *parentNode = childNode->parent();

    if (parentNode == m_pRootNode.get()) {
        return QModelIndex();
    }

    return createIndex(parentNode->row(), 0, parentNode);
}

int CustomItemModel::rowCount(const QModelIndex &parent) const  {
    if (parent.column() > 0) {
        return 0;
    }

    MyItemNode *parentNode = nodeFromIndex(parent);
    return parentNode? parentNode->childCount() : 0;
}

int CustomItemModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 1;//只有一列
}

// 在自定义的数据模型类中重写 headerData 方法来定制表头的显示
QVariant CustomItemModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        if (section == 0) {
            return "Column 1";
        } else if (section == 1) {
            return "Column 2";
        }
    }
    return QVariant();
}


QVariant CustomItemModel::data(const QModelIndex &index, int role) const {
    if(!index.isValid()) {
        return QVariant();
    }

    if(role == Qt::DisplayRole || role == Qt::EditRole) {
        return nodeFromIndex(index)->data();
    }

    return QVariant();
}

