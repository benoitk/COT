QT -= core gui

!linux {
    DEFINES +=HAVE_DECL_TIOCSRS485=0
}

HEADERS += \
    config.h \
    src/modbus.h \
    src/modbus-private.h \
    src/modbus-rtu.h \
    src/modbus-rtu-private.h \
    src/modbus-tcp.h \
    src/modbus-tcp-private.h \
    src/modbus-version.h
SOURCES += \
    src/modbus.c \
    src/modbus-data.c \
    src/modbus-rtu.c \
    src/modbus-tcp.c

TEMPLATE = lib
TARGET = modbus
DESTDIR = $${top_builddir}/lib

