#ifndef JSONTREEITEM_H
#define JSONTREEITEM_H

#include <QJsonValue>

class JsonTreeItem {
public:
    JsonTreeItem(const QString &key, const QJsonValue &value, JsonTreeItem *parent = nullptr);
    ~JsonTreeItem();

    void appendChild(JsonTreeItem *child);
    JsonTreeItem *child(int row) const;
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    JsonTreeItem *parentItem();

    QJsonValue value() const;
    void setValue(const QJsonValue &value);
    QJsonValue toJson() const;
    bool isExpanded() const;
    void setExpanded(bool expanded);

private:
    QString m_key;
    QJsonValue m_value;
    QList<JsonTreeItem*> m_children;
    JsonTreeItem *m_parentItem;
    bool m_expanded;
};

#endif // JSONTREEITEM_H
