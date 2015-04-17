TEMPLATE = app
TARGET = cot
CONFIG *= c++11
CONFIG *= depend_includepath

QT *= widgets

include( "../outdirs.pri" )
include( "../g++.pri" )

COTLIB_PWD = $${PWD}/../libcot

INCLUDEPATH *=  \
    $${COTLIB_PWD} \
    $${COTLIB_PWD}/gui \
    $${COTLIB_PWD}/automate/variables \
    $${COTLIB_PWD}/automate

COTWIDGETS_LIBDIR = $${OUT_PWD}/../lib
QMAKE_RPATHDIR *= $$COTWIDGETS_LIBDIR
LIBS *= -L$$COTWIDGETS_LIBDIR -lcotwidgets
macx:PRE_TARGETDEPS *= $${COTWIDGETS_LIBDIR}

SOURCES *= main.cpp
