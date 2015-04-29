TEMPLATE = app
TARGET = cot-translator
include("$${top_srcdir}/config.pri")
macx:CONFIG -= app_bundle
QT *= core-private

INCLUDEPATH *= \
    . \
    3rdparty

DEPENDPATH *= \
    . \
    3rdparty

HEADERS *= \
    3rdparty/simtexth.h \
    3rdparty/translator.h \
    3rdparty/translatormessage.h \
    CTranslator.h

SOURCES *= main.cpp \
    3rdparty/numerus.cpp \
    3rdparty/qm.cpp \
    3rdparty/simtexth.cpp \
    3rdparty/translator.cpp \
    3rdparty/translatormessage.cpp \
    3rdparty/ts.cpp \
    CTranslator.cpp

DISTFILES *= \
    README.txt
