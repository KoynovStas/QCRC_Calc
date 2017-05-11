QT += testlib
QT += quick



CONFIG += c++11
CONFIG += qt warn_on depend_includepath testcase
CONFIG += debug_and_release  build_all

CONFIG -= app_bundle


DEFINES += TEST=1




# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS


# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0




SRC_PATH = $$PWD/../src


INCLUDEPATH = $$SRC_PATH




CONFIG(debug, debug|release) {
    TARGETDIR = debug
    DESTDIR   = debug
}


CONFIG(release, debug|release) {
    TARGETDIR = release
    DESTDIR   = release
}
