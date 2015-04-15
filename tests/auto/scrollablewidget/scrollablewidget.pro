TARGET = scrollablewidgettest
QT += widgets testlib

COTWIDGETS_LIBDIR = $${OUT_PWD}/../../../lib

include( "$${PWD}/../../../outdirs.pri" )

QMAKE_RPATHDIR += $$COTWIDGETS_LIBDIR

INCLUDEPATH +=  $${PWD}/../../../libcot/keyboards/
DEPENDPATH += $${PWD}/../../../libcot/keyboards/


LIBS += -L$$COTWIDGETS_LIBDIR -lcotwidgets

SOURCES  += scrollablewidgettest.cpp

