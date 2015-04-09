TARGET = numericalkeyboardwidgettest
QT += widgets testlib
SOURCES  += numericalkeyboardwidgettest.cpp ../../../../cot/keyboards/numericalkeyboardwidget.cpp \
             ../../../../cot/keyboards/keyboardnormalbutton.cpp \
            ../../../../cot/keyboards/keyboardbuttonbase.cpp ../../../../cot/keyboards/keyboardspecialbutton.cpp

HEADERS += ../../../../cot/keyboards/numericalkeyboardwidget.h \
            ../../../../cot/keyboards/keyboardnormalbutton.h ../../../../cot/keyboards/keyboardspecialbutton.h \
            ../../../../cot/keyboards/keyboardbuttonbase.h \
