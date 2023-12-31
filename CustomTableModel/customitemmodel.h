#ifndef CUSTOMITEMMODEL_H
#define CUSTOMITEMMODEL_H


#include <QAbstractItemModel>
#include <QVector>
#include <QVariant>
#include <QModelIndex>
#include <QTreeView>


class MyItemNode {
public:
    explicit MyItemNode(const QString &name, MyItemNode *parent = nullptr)
        : m_name(name), m_parent(parent) {}

    ~MyItemNode() {
        qDeleteAll(m_children);
    }

    void addChild(MyItemNode *child) {
        m_children.append(child);
    }

    MyItemNode *child(int row) const {
        return m_children.value(row);
    }

    int childCount() const {
        return m_children.count();
    }

    int row() const {
        if (m_parent)
            return m_parent->m_children.indexOf(const_cast<MyItemNode*>(this));
        return 0;
    }

    QVariant data() const {
        return m_name;
    }

    MyItemNode* parent() const {
        return m_parent;
    }

    inline void setName(QString&& name) {
        m_name = std::move(name);
    }

private:
    QString m_name;
    MyItemNode *m_parent;
    QList<MyItemNode*> m_children;
};


class CustomItemModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit CustomItemModel(QObject *parent = nullptr);

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                            int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public:
    void setRootNode(MyItemNode* node) {
        m_pRootNode.reset(node);
    }
private:
    MyItemNode *nodeFromIndex(const QModelIndex &index) const {
        if (index.isValid()) {
            return static_cast<MyItemNode*>(index.internalPointer());
        } else {
            return m_pRootNode.get();
        }
    }

    std::unique_ptr<MyItemNode> m_pRootNode;

};

#endif // CUSTOMITEMMODEL_H
