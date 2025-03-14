#include "JsonTreeItem.h"
#include <QJsonArray>
#include <QJsonObject>

JsonTreeItem::JsonTreeItem(const QString &key, const QJsonValue &value, JsonTreeItem *parent)
    : m_key(key), m_value(value), m_parentItem(parent), m_expanded(false) {}

JsonTreeItem::~JsonTreeItem() {
    qDeleteAll(m_children);
}

void JsonTreeItem::appendChild(JsonTreeItem *child) {
    m_children.append(child);
}

JsonTreeItem *JsonTreeItem::child(int row) const {
    return m_children.value(row);
}

int JsonTreeItem::childCount() const {
    return m_children.count();
}

int JsonTreeItem::columnCount() const {
    return 2; // Key and Value
}

QJsonValue JsonTreeItem::toJson() const {
    if (m_value.isObject()) {
        QJsonObject obj;
        for (const auto &child : m_children) {
            obj.insert(child->data(0).toString(), child->toJson());
        }
        return obj;
    } else if (m_value.isArray()) {
        QJsonArray array;
        for (const auto &child : m_children) {
            array.append(child->toJson());
        }
        return array;
    } else {
        return m_value; // for primitive types like strings, numbers, booleans, null
    }
}
