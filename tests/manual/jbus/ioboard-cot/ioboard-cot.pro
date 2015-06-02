TARGET = ioboard-cot

include("$${top_srcdir}/config.pri")

SOURCES += ioboard-cot.cpp

INCLUDEPATH += $${top_srcdir}/3rd_party/libmodbus/src
LIBS +=  -L$${LIBCOT_BUILD_PWD} -lmodbus
