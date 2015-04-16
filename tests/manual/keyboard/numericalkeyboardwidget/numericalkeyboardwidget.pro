TARGET = numericalkeyboardwidget
QT += widgets
SOURCES += main.cpp widget.cpp localcombobox.cpp

HEADERS += widget.h localcombobox.h
include( "$$top_srcdir/tests/tests.pri" )
