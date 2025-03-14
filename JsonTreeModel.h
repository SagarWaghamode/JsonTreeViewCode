#ifndef JSONTREEMODEL_H
#define JSONTREEMODEL_H

#include <QAbstractItemModel>
#include <QJsonObject>

class JsonTreeItem;

class JsonTreeModel : public QAbstractItemModel {
    Q_OBJECT
public:
    explicit JsonTreeModel(QObject *parent = nullptr);
    ~JsonTreeModel() override;

    void loadJson(const QJsonObject &jsonObject);
    QJsonValue toJson() const;
    Q_INVOKABLE void saveToFile();

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Q_INVOKABLE bool isExpanded(const QModelIndex &index) const;
    Q_INVOKABLE void setExpanded(const QModelIndex &index, bool expanded);
private:
    void parseJson(const QJsonValue &value, JsonTreeItem *parentItem);

    JsonTreeItem *m_rootItem;

};

#endif // JSONTREEMODEL_H
