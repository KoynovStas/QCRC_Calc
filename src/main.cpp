#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "qucrc_t.h"
#include "crc_calc_for_text.h"
#include "crc_calc_for_hex.h"



int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QuCRC_t uCRC;

    CRC_Calc_for_Text calc_text;
    CRC_Calc_for_Hex  calc_hex;

    calc_text.set_ucrc(&uCRC);
    calc_hex.set_ucrc(&uCRC);


    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("uCRC", &uCRC);
    engine.rootContext()->setContextProperty("calc_text", &calc_text);
    engine.rootContext()->setContextProperty("calc_hex", &calc_hex);
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    return app.exec();
}
