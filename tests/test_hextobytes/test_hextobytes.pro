TEMPLATE = app


QT       -= gui
CONFIG   += console



include(../common.pri)




SOURCES += test_hextobytes.cpp        \
           $$SRC_PATH/hextobytes.cpp


HEADERS += $$SRC_PATH/hextobytes.h
