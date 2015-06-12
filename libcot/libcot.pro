TEMPLATE = lib
TARGET = cotlib
QT *= widgets

include("$${top_srcdir}/config.pri")

include(cotlib.pri)

DEFINES += LIBCOT_BUILD

DEVICE_BUILD {
      DEFINES += JSON_DIRECTORY=\"\\\"/home/seres/\\\"\"
} else {
      DEFINES += JSON_DIRECTORY=\"\\\"$${top_srcdir}/libcot/\\\"\"
}

jsonfile.path = /home/seres/
jsonfile.files = save.json
INSTALLS += jsonfile
