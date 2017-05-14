#include "application.h"

#ifdef Q_OS_WIN
    #include <windows.h>  //need for support console (It's Windows baby)
#endif

#include <iostream>





Application::Application(int &argc, char **argv) :
    QGuiApplication(argc, argv)
{
    setApplicationDisplayName("CRC Calculator ver " +
                              QString::number(MAJOR_VERSION) + '.' +
                              QString::number(MINOR_VERSION));

    attach_console();


    calc_text.set_ucrc(&uCRC);
    calc_hex.set_ucrc(&uCRC);


    // GUI
    engine.rootContext()->setContextProperty("uCRC", &uCRC);
    engine.rootContext()->setContextProperty("calc_text", &calc_text);
    engine.rootContext()->setContextProperty("calc_hex", &calc_hex);

    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));
}



void Application::attach_console()
{

#ifdef Q_OS_WIN

    // attach the new console to this application's process
    AttachConsole(ATTACH_PARENT_PROCESS);

   // reopen the std I/O streams to redirect I/O to the new console
   freopen("CON", "w", stdout);
   freopen("CON", "w", stderr);
   freopen("CON", "r", stdin);

#endif

}
