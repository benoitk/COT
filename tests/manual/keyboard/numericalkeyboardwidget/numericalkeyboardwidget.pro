TARGET = numericalkeyboardwidget
QT *= widgets

include("$${top_srcdir}/config.pri")

HEADERS *= widget.h localcombobox.h
SOURCES *= main.cpp widget.cpp localcombobox.cpp
