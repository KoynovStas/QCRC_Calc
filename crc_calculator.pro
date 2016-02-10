TEMPLATE = app
TARGET   = CRC_Calculator


QT += core
QT += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



DEFINES += MAJOR_VERSION=1
DEFINES += MINOR_VERSION=0



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
           mainwindow.cpp \
           bitwidget.cpp \
           bitset64.cpp \
           ucrc_t.cpp \
           qucrc_t.cpp \
           hextobytes.cpp \
           crc_calc_for_hex.cpp \
           crc_calc_for_text.cpp



HEADERS += mainwindow.h \
           bitwidget.h \
           bitset64.h \
           ucrc_t.h \
           qucrc_t.h \
           qexecthread.h \
           hextobytes.h \
           crc_calc_for_hex.h \
           crc_calc_for_text.h



FORMS   += mainwindow.ui
