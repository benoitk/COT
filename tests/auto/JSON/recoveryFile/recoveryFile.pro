TARGET = recoveryFileTest
QT += testlib
CONFIG += testcase

include("$${top_srcdir}/config.pri")

SOURCES  += recoveryFileTest.cpp

DISTFILES += $${top_srcdir}/libcot/save.json
