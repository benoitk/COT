TARGET = recoveryFileTest
QT += testlib


include("$${top_srcdir}/config.pri")

SOURCES  += recoveryFileTest.cpp

DISTFILES += $${top_srcdir}/libcot/save.json
DEFINES += COT_JSON_FILE_PATH=\"\\\"$${top_srcdir}/libcot/save.json\\\"\"
