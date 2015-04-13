TARGET = keyboardnormalbuttontest
QT += widgets testlib

COTWIDGETS_LIBDIR = $${OUT_PWD}/../../../../lib


QMAKE_RPATHDIR += $$COTWIDGETS_LIBDIR

INCLUDEPATH +=  $${PWD}/../../../../libcot/keyboards/
DEPENDPATH += $${PWD}/../../../../libcot/keyboards/


LIBS += -L$$COTWIDGETS_LIBDIR -lcotwidgets
QT += widgets testlib
SOURCES  += keyboardnormalbuttontest.cpp
 
