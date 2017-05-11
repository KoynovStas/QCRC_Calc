TEMPLATE = app


include(../common.pri)




SOURCES += test_qucrc_t.cpp       \
           $$SRC_PATH/qucrc_t.cpp \
           $$SRC_PATH/ucrc_t.cpp


HEADERS += $$SRC_PATH/qucrc_t.h \
           $$SRC_PATH/ucrc_t.h
