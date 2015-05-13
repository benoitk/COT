# $$top_builddir
# $$top_srcdir

KPLOTTING_SRC_PWD = $${top_srcdir}/3rd_party/kplotting/
LIBCOT_SRC_PWD = $${top_srcdir}/libcot
LIBCOT_BUILD_PWD = $${top_builddir}/lib


target.path = /home/seres/
INSTALLS += target

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
    $${LIBCOT_SRC_PWD}/gui/tools/configurator \
    $${LIBCOT_SRC_PWD}/gui/tools/configurator/actions \
    $${LIBCOT_SRC_PWD}/gui/tools/configurator/cycles \
    $${LIBCOT_SRC_PWD}/gui/tools/configurator/display \
    $${LIBCOT_SRC_PWD}/gui/tools/configurator/extensions \
    $${LIBCOT_SRC_PWD}/gui/tools/configurator/hardware \
    $${LIBCOT_SRC_PWD}/gui/tools/configurator/network \
    $${LIBCOT_SRC_PWD}/gui/tools/configurator/sequencer \
    $${LIBCOT_SRC_PWD}/gui/tools/configurator/streams \
    $${LIBCOT_SRC_PWD}/gui/tools/configurator/variables \
    $${LIBCOT_SRC_PWD}/gui/widgets \
    $${LIBCOT_SRC_PWD}/automate/variables \
    $${LIBCOT_SRC_PWD}/automate \
    $${LIBCOT_SRC_PWD}/automate/com \
    $${LIBCOT_SRC_PWD}/automate/cycles \
    $${LIBCOT_SRC_PWD}/automate/actions \
    $${LIBCOT_SRC_PWD}/automate/units \
    $${LIBCOT_SRC_PWD}/updater \
    $${LIBCOT_SRC_PWD}/keyboards \
    $${LIBCOT_SRC_PWD}/graphics \
    $${LIBCOT_SRC_PWD}/automate/organs/ \
    $${KPLOTTING_SRC_PWD}/src \

isEqual(TEMPLATE, "app") {
    QMAKE_RPATHDIR *= $${LIBCOT_BUILD_PWD}
    LIBS *= -L$${LIBCOT_BUILD_PWD} -lcotlib

    LIBCOT_STATIC_BUILD {
        PRE_TARGETDEPS *= $${LIBCOT_BUILD_PWD}
    }
} else:isEqual(TEMPLATE, "lib") {
    LIBCOT_STATIC_BUILD {
        CONFIG -= shared
        CONFIG *= static
    }

    isEqual(TARGET, "cotlib") {
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
    -Wnon-virtual-dtor -Wundef  \
    -Wchar-subscripts -Wpointer-arith \
    -Wwrite-strings -Wpacked -Wformat-security \
    -Wmissing-format-attribute -Woverloaded-virtual

  # gives warnings in Qt itself
  #-Wcast-align
  # qCDebug is incompatible with -pedantic, see http://lists.qt-project.org/pipermail/development/2014-August/018022.html
  #NORMAL_CFLAGS *= -pedantic

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
