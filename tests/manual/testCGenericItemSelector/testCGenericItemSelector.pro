# Simple application to test the testCGenericItemSelector dialog

QT       += widgets
TARGET = testCGenericItemSelector
TEMPLATE = app
CONFIG += c++11

COTWIDGETS_LIBDIR = $${OUT_PWD}/../../../lib
COTWIDGETS_SRCDIR = $${PWD}/../../../libcot

QMAKE_RPATHDIR += $$COTWIDGETS_LIBDIR

INCLUDEPATH +=  $${COTWIDGETS_SRCDIR} \
                $${COTWIDGETS_SRCDIR}/gui/ \
                $${COTWIDGETS_SRCDIR}/gui/widgets \
                $${COTWIDGETS_SRCDIR}/automate/ \
                $${COTWIDGETS_SRCDIR}/automate/variables/

DEPENDPATH +=   $${COTWIDGETS_SRCDIR}/gui/ \
                $${COTWIDGETS_SRCDIR}/automate/ \
                $${COTWIDGETS_SRCDIR}/automate/variables/

LIBS += -L$$COTWIDGETS_LIBDIR -lcotwidgets

SOURCES += main.cpp
