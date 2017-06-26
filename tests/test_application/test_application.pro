TEMPLATE = app


QT       -= gui
CONFIG   += console



include(../common.pri)




SOURCES += test_application.cpp             \
           $$SRC_PATH/abstract_crc_calc.cpp \
           $$SRC_PATH/application.cpp       \
           $$SRC_PATH/crc_calc_for_hex.cpp  \
           $$SRC_PATH/crc_calc_for_text.cpp \
           $$SRC_PATH/crc_result.cpp        \
           $$SRC_PATH/hextobytes.cpp        \
           $$SRC_PATH/qucrc_t.cpp           \
           $$SRC_PATH/ucrc_t.cpp


HEADERS += $$SRC_PATH/abstract_crc_calc.h \
           $$SRC_PATH/crc_calc_for_text.h \
           $$SRC_PATH/crc_calc_for_hex.h  \
           $$SRC_PATH/application.h       \
           $$SRC_PATH/crc_result.h        \
           $$SRC_PATH/hextobytes.h        \
           $$SRC_PATH/qucrc_t.h           \
           $$SRC_PATH/ucrc_t.h
