TARGET = jbus
QT += testlib network
CONFIG += testcase

include("$${top_srcdir}/config.pri")

SOURCES += jbustest.cpp

INCLUDEPATH += $${top_srcdir}/3rd_party/libmodbus/src
LIBS +=  -L$${LIBCOT_BUILD_PWD} -lmodbus
