TEMPLATE = lib
TARGET = cotlib
QT *= widgets

include("$${top_srcdir}/config.pri")

include(cotlib.pri)

DEFINES += LIBCOT_BUILD

DEFINES += JSON_DIRECTORY=\"\\\"$${top_srcdir}/libcot/\\\"\"

INCLUDEPATH += $${top_srcdir}/3rd_party/libmodbus/src
LIBS += -lmodbus -L$${LIBCOT_BUILD_PWD}
