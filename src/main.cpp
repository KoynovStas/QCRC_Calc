#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "qucrc_t.h"





int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QuCRC_t uCRC;


    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("uCRC", &uCRC);
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    return app.exec();
}
