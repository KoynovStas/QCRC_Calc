TEMPLATE = app
TARGET   = CRC_Calculator


QT += core
QT += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



CONFIG += qt
CONFIG += debug_and_release  build_all



CONFIG(debug, debug|release) {
    TARGETDIR = debug
    DESTDIR   = debug
}



CONFIG(release, debug|release) {
    TARGETDIR = release
    DESTDIR   = release
}



# Input
SOURCES += main.cpp \
           mainwindow.cpp



HEADERS += mainwindow.h



FORMS   += mainwindow.ui
