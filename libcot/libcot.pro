TEMPLATE = lib
TARGET = cotlib
QT *= widgets

include("$${top_srcdir}/config.pri")

include(cotlib.pri)

DEFINES += LIBCOT_BUILD

jsonfile.path = /home/seres/
jsonfile.files = save.json
INSTALLS += jsonfile

TRANSLATIONS    = en_US.ts \
                              fr_FR.ts \
                              ru_RU.ts
