TEMPLATE = app


QT       -= gui
CONFIG   += console



include(../common.pri)




SOURCES += test_crc_calc_for_text.cpp       \
           $$SRC_PATH/abstract_crc_calc.cpp \
           $$SRC_PATH/crc_calc_for_text.cpp \
           $$SRC_PATH/crc_result.cpp        \
           $$SRC_PATH/hextobytes.cpp        \
           $$SRC_PATH/qucrc_t.cpp           \
           $$SRC_PATH/ucrc_t.cpp


HEADERS += $$SRC_PATH/abstract_crc_calc.h \
           $$SRC_PATH/crc_calc_for_text.h \
           $$SRC_PATH/crc_result.h        \
           $$SRC_PATH/hextobytes.h        \
           $$SRC_PATH/qucrc_t.h           \
           $$SRC_PATH/ucrc_t.h
