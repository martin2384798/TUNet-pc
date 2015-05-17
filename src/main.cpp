#include <QGuiApplication>
#include <QQmlEngine>
#include <QtQml>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///qml/qml/Main.qml")));
//    engine.rootContext()->setContextProperty("yx","Color");
    return app.exec();
}
