TARGET = keyboardwidget
QT += widgets
SOURCES  += main.cpp ../../../../cot/keyboards/keyboardwidget.cpp ../../../../cot/keyboards/keyboardlayoututils.cpp \
             ../../../../cot/keyboards/keyboardnormalbutton.cpp \
            ../../../../cot/keyboards/keyboardbuttonbase.cpp ../../../../cot/keyboards/keyboardspecialbutton.cpp \
    widget.cpp localcombobox.cpp

HEADERS += ../../../../cot/keyboards/keyboardwidget.h ../../../../cot/keyboards/keyboardlayoututils.h \
            ../../../../cot/keyboards/keyboardnormalbutton.h ../../../../cot/keyboards/keyboardspecialbutton.h \
            ../../../../cot/keyboards/keyboardbuttonbase.h \
    widget.h localcombobox.h

