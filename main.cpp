#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFile>
#include <QJsonDocument>
#include "JsonTreeModel.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    // Load JSON file
    QString filePath = "D:/AGAS/New Folder/JsonTreeViewCode/sample.json";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qFatal("Failed to open JSON file");
        return -1;
    }

    QByteArray jsonData = file.readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
    file.close();

    JsonTreeModel jsonModel;
    jsonModel.loadJson(jsonDoc.object());

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("jsonTreeModel", &jsonModel);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty()) return -1;

    return app.exec();
}
