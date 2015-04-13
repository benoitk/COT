TARGET = keyboardwidget
QT += widgets
SOURCES += main.cpp widget.cpp localcombobox.cpp

HEADERS += widget.h localcombobox.h

COTWIDGETS_LIBDIR = $${OUT_PWD}/../../../../lib


QMAKE_RPATHDIR += $$COTWIDGETS_LIBDIR

INCLUDEPATH +=  $${PWD}/../../../../libcot/keyboards/
DEPENDPATH += $${PWD}/../../../../libcot/keyboards/


LIBS += -L$$COTWIDGETS_LIBDIR -lcotwidgets


