# $$top_builddir
# $$top_srcdir

LIBCOT_SRC_PWD = $${top_srcdir}/libcot
LIBCOT_BUILD_PWD = $${top_builddir}/lib

DEVICE_BUILD {
    DEFINES *= DEVICE_BUILD
    DEFINES *= LIBCOT_STATIC_BUILD
}

LIBCOT_STATIC_BUILD {
    DEFINES *= LIBCOT_STATIC_BUILD
}

DEFINES *= \
    QT_NO_CAST_TO_ASCII \
    QT_USE_FAST_CONCATENATION \
    QT_USE_FAST_OPERATOR_PLUS \
    QT_STRICT_ITERATORS

DEFINES *= "COT_JSON_FILE=\\\"$${LIBCOT_SRC_PWD}/save.json\\\""
macx:DEFINES *= "COT_USB_MOUNT_POINT=\\\"/Volumes\\\""
else:DEFINES *= "COT_USB_MOUNT_POINT=\\\"/media\\\""

CONFIG *= \
    c++11 \
    depend_includepath

INCLUDEPATH *= \
    . \
    $${LIBCOT_SRC_PWD} \
    $${LIBCOT_SRC_PWD}/gui \
    $${LIBCOT_SRC_PWD}/gui/measure \
    $${LIBCOT_SRC_PWD}/gui/panel \
    $${LIBCOT_SRC_PWD}/gui/tools \
    $${LIBCOT_SRC_PWD}/gui/tools/electrical-tests \
    $${LIBCOT_SRC_PWD}/gui/tools/history \
    $${LIBCOT_SRC_PWD}/gui/tools/log-files \
    $${LIBCOT_SRC_PWD}/gui/tools/maintenance \
    $${LIBCOT_SRC_PWD}/gui/tools/options \
    $${LIBCOT_SRC_PWD}/gui/widgets \
    $${LIBCOT_SRC_PWD}/automate/variables \
    $${LIBCOT_SRC_PWD}/automate \
    $${LIBCOT_SRC_PWD}/automate/com \
    $${LIBCOT_SRC_PWD}/automate/cycles \
    $${LIBCOT_SRC_PWD}/automate/actions \
    $${LIBCOT_SRC_PWD}/automate/units \
    $${LIBCOT_SRC_PWD}/updater \
    $${LIBCOT_SRC_PWD}/keyboards

isEqual(TEMPLATE, "app") {
    QMAKE_RPATHDIR *= $${LIBCOT_BUILD_PWD}
    LIBS *= -L$${LIBCOT_BUILD_PWD} -lcot

    LIBCOT_STATIC_BUILD {
        PRE_TARGETDEPS *= $${LIBCOT_BUILD_PWD}
    }
} else:isEqual(TEMPLATE, "lib") {
    LIBCOT_STATIC_BUILD {
        CONFIG -= shared
        CONFIG *= static
    }

    isEqual(TARGET, "cot") {
        DEFINES *= LIBCOT_BUILD
        DESTDIR = $${LIBCOT_BUILD_PWD}
    }

    macx:CONFIG -= lib_bundle
}

unix {
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
  UI_DIR = .ui
} else {
  MOC_DIR = _moc
  OBJECTS_DIR = _obj
  UI_DIR = _ui
}

*-g++* {
  NORMAL_CFLAGS = -Wno-long-long
  #-ansi gives error with mingw
  NORMAL_CXXFLAGS = \
    -Wnon-virtual-dtor -Wundef -Wcast-align \
    -Wchar-subscripts -Wpointer-arith \
    -Wwrite-strings -Wpacked -Wformat-security \
    -Wmissing-format-attribute -Woverloaded-virtual

  NORMAL_CFLAGS *= -pedantic

  debug:NORMAL_CXXFLAGS *= -O0 -g3
  debug:NORMAL_CXXFLAGS -= -g
  USABLE_CXXFLAGS = -Wold-style-cast
  HARD_CXXFLAGS = -Weffc++ -Wshadow
  PITA_CXXFLAGS = -Wunreachable-code
  david:QMAKE_CXXFLAGS *= -Werror

  QMAKE_CFLAGS   *= $$NORMAL_CFLAGS
  QMAKE_CXXFLAGS *= $$NORMAL_CFLAGS $$NORMAL_CXXFLAGS

  # Not needed - warn_on.prf adds QMAKE_CXXFLAGS_WARN_ON to QMAKE_CXXFLAGS
  #QMAKE_CFLAGS_WARN_ON   *= $$NORMAL_CFLAGS
  #QMAKE_CXXFLAGS_WARN_ON *= $$NORMAL_CFLAGS $$NORMAL_CXXFLAGS

  QMAKE_CXXFLAGS_WARN_ON *= $$USABLE_CXXFLAGS
  #QMAKE_CXXFLAGS_WARN_ON *= $$HARD_CXXFLAGS # headers must compile with this, code doesn't need to; needs patched Qt
  #QMAKE_CXXFLAGS_WARN_ON *= $$PITA_CXXFLAGS # header would be nice, but it's probably pointless, due to noise from Qt and libstdc++

  CONFIG *= hide_symbols
}