#include "application.h"





Application::Application(int &argc, char **argv) :
    QGuiApplication(argc, argv)
{
    setApplicationDisplayName("CRC Calculator ver " +
                              QString::number(MAJOR_VERSION) + '.' +
                              QString::number(MINOR_VERSION));



    calc_text.set_ucrc(&uCRC);
    calc_hex.set_ucrc(&uCRC);

    engine.rootContext()->setContextProperty("uCRC", &uCRC);
    engine.rootContext()->setContextProperty("calc_text", &calc_text);
    engine.rootContext()->setContextProperty("calc_hex", &calc_hex);

    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));
}
