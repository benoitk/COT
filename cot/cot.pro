TEMPLATE = app
TARGET = cot
CONFIG *= c++11
QT *= widgets

COTWIDGETS_LIBDIR = $${OUT_PWD}/../lib

QMAKE_RPATHDIR += $$COTWIDGETS_LIBDIR

INCLUDEPATH +=  $${PWD}/../libcot/gui/ $${PWD}/../libcot/automate/variables/ $${PWD}/../libcot/automate/
DEPENDPATH += $${PWD}/../libcot/gui/ $${PWD}/../libcot/automate/variables/ $${PWD}/../libcot/automate/

LIBS += -L$$COTWIDGETS_LIBDIR -lcotwidgets

SOURCES *= main.cpp \
