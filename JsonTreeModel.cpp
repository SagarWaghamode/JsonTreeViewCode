#include "JsonTreeModel.h"
#include <QVariant>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "JsonTreeItem.h"

QJsonValue JsonTreeModel::toJson() const {
    return m_rootItem->toJson();
}

void JsonTreeModel::saveToFile() {
    QString filePath = "D:/AGAS/New Folder/JsonTreeViewCode/sample.json";

    // Retrieve the JSON value from the model
    QJsonValue jsonValue = toJson();

    // Initialize the QJsonDocument to hold the JSON data
    QJsonDocument doc;

    // Check if the JSON value is valid before proceeding
    if (jsonValue.isObject()) {
        doc.setObject(jsonValue.toObject());
    } else if (jsonValue.isArray()) {
        doc.setArray(jsonValue.toArray());
    } else {
        qWarning() << "Invalid JSON value from toJson()";
        return;
    }

    // Attempt to open the file in write mode
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Write JSON data with indentation (pretty print)
        file.write(doc.toJson(QJsonDocument::Indented));

        // Ensure the changes are flushed
        file.flush();
        file.close();
    } else {
        qWarning() << "Could not open file for writing:" << filePath;
    }
}


QVariant JsonTreeItem::data(int column) const {
    if (column == 0) return m_key;
    if (column == 1) {
        if (m_value.isString()) return m_value.toString();
        if (m_value.isBool()) return m_value.toBool() ? "true" : "false";
        if (m_value.isDouble()) return m_value.toDouble();
        if (m_value.isNull()) return "null";
        if (m_value.isObject()) return "Object";
        if (m_value.isArray()) return "Array";
    }
    return QVariant();
}

int JsonTreeItem::row() const {
    if (m_parentItem) return m_parentItem->m_children.indexOf(const_cast<JsonTreeItem*>(this));
    return 0;
}

JsonTreeItem *JsonTreeItem::parentItem() {
    return m_parentItem;
}

JsonTreeModel::JsonTreeModel(QObject *parent)
    : QAbstractItemModel(parent), m_rootItem(new JsonTreeItem("Root", QJsonValue())) {}

JsonTreeModel::~JsonTreeModel() {
    delete m_rootItem;
}

void JsonTreeModel::loadJson(const QJsonObject &jsonObject) {
    beginResetModel();
    parseJson(QJsonValue(jsonObject), m_rootItem);
    endResetModel();
}

QModelIndex JsonTreeModel::index(int row, int column, const QModelIndex &parent) const {
    JsonTreeItem *parentItem;
    if (!parent.isValid()) {
        parentItem = m_rootItem;  // Root item
    } else {
        parentItem = static_cast<JsonTreeItem*>(parent.internalPointer());
    }

    // Get the child item
    JsonTreeItem *childItem = parentItem->child(row);
    if (childItem) {
        return createIndex(row, column, childItem);
    }

    return QModelIndex();  // Invalid index if no child exists
}

QModelIndex JsonTreeModel::parent(const QModelIndex &index) const {
    if (!index.isValid()) return QModelIndex();

    JsonTreeItem *childItem = static_cast<JsonTreeItem*>(index.internalPointer());
    JsonTreeItem *parentItem = childItem->parentItem();

    if (parentItem == m_rootItem) return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int JsonTreeModel::rowCount(const QModelIndex &parent) const {
    JsonTreeItem *parentItem = !parent.isValid() ? m_rootItem : static_cast<JsonTreeItem*>(parent.internalPointer());
    return parentItem->childCount();
}

int JsonTreeModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 2; // Key and Value
}

QVariant JsonTreeModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();

    JsonTreeItem *item = static_cast<JsonTreeItem*>(index.internalPointer());
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        return item->data(index.column());
    }
    return QVariant();
}

Qt::ItemFlags JsonTreeModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

bool JsonTreeModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    beginResetModel();
    if (!index.isValid() || role != Qt::EditRole)
        return false;
    // Update the JSON structure based on the index and new value
    JsonTreeItem* item = static_cast<JsonTreeItem*>(index.internalPointer());
    item->setValue(QJsonValue(value.toString()));
    endResetModel();
    return true;
}

void JsonTreeModel::parseJson(const QJsonValue &value, JsonTreeItem *parentItem) {
    if (value.isObject()) {
        QJsonObject jsonObject = value.toObject();
        for (auto it = jsonObject.begin(); it != jsonObject.end(); ++it) {
            JsonTreeItem *item = new JsonTreeItem(it.key(), it.value(), parentItem);
            parentItem->appendChild(item);
            parseJson(it.value(), item);
        }
    } else if (value.isArray()) {
        QJsonArray jsonArray = value.toArray();
        for (int i = 0; i < jsonArray.size(); ++i) {
            JsonTreeItem *item = new JsonTreeItem(QString::number(i), jsonArray.at(i), parentItem);
            parentItem->appendChild(item);
            parseJson(jsonArray.at(i), item);
        }
    }
}

QJsonValue JsonTreeItem::value() const {
    return m_value;
}

void JsonTreeItem::setValue(const QJsonValue &value) {
    m_value = value;
}

bool JsonTreeModel::isExpanded(const QModelIndex &index) const {
    if (!index.isValid()) return false;

    JsonTreeItem *item = static_cast<JsonTreeItem*>(index.internalPointer());
    return item->isExpanded();
}

bool JsonTreeItem::isExpanded() const {
    return m_expanded;
}

void JsonTreeItem::setExpanded(bool expanded) {
    m_expanded = expanded;
}

void JsonTreeModel::setExpanded(const QModelIndex &index, bool expanded) {
    if (!index.isValid()) return;
    beginResetModel();
    JsonTreeItem *item = static_cast<JsonTreeItem*>(index.internalPointer());
    item->setExpanded(expanded);
    endResetModel();
}



