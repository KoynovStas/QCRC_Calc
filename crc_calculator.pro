TEMPLATE = app
TARGET   = CRC_Calculator

QT += quick quickcontrols2



DEFINES += MAJOR_VERSION=1
DEFINES += MINOR_VERSION=0




CONFIG += c++11
CONFIG += debug_and_release  build_all


CONFIG(debug, debug|release) {
    TARGETDIR = debug
    DESTDIR   = debug
}


CONFIG(release, debug|release) {
    TARGETDIR = release
    DESTDIR   = release
}




# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = qml controls



# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =



# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS



# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0




# Input
SOURCES += src/*.cpp



HEADERS += src/*.h



RESOURCES += qtquickcontrols2.conf         \
             $$files(qml/*.qml)            \
             $$files(qml/controls/*.qml)

