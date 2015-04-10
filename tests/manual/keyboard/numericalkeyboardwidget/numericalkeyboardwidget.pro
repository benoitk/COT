TARGET = numericalkeyboardwidget
QT += widgets
SOURCES  += main.cpp ../../../../cot/keyboards/numericalkeyboardwidget.cpp  \
             ../../../../cot/keyboards/keyboardnormalbutton.cpp \
            ../../../../cot/keyboards/keyboardbuttonbase.cpp ../../../../cot/keyboards/keyboardspecialbutton.cpp \
    widget.cpp \
    localcombobox.cpp

HEADERS += ../../../../cot/keyboards/numericalkeyboardwidget.h \
            ../../../../cot/keyboards/keyboardnormalbutton.h ../../../../cot/keyboards/keyboardspecialbutton.h \
            ../../../../cot/keyboards/keyboardbuttonbase.h \
    widget.h \
    localcombobox.h

