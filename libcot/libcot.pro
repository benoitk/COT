TEMPLATE = lib
TARGET = cotlib
QT *= widgets

include("$${top_srcdir}/config.pri")

include(cotlib.pri)

DEFINES += LIBCOT_BUILD

DEFINES += JSON_DIRECTORY=\"\\\"$${top_srcdir}/libcot/\\\"\"
