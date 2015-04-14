*-g++* {
  NORMAL_CFLAGS = -Wno-long-long 
  #-ansi gives error with mingw
  NORMAL_CXXFLAGS = \
	-Wnon-virtual-dtor -Wundef -Wcast-align \
	-Wchar-subscripts -Wpointer-arith \
	-Wwrite-strings -Wpacked -Wformat-security \
	-Wmissing-format-attribute -Woverloaded-virtual

  NORMAL_CFLAGS += -pedantic

  debug:NORMAL_CXXFLAGS += -O0 -g3
  debug:NORMAL_CXXFLAGS -= -g
  USABLE_CXXFLAGS = -Wold-style-cast
  HARD_CXXFLAGS = -Weffc++ -Wshadow
  PITA_CXXFLAGS = -Wunreachable-code
  david:QMAKE_CXXFLAGS += -Werror

  QMAKE_CFLAGS   += $$NORMAL_CFLAGS
  QMAKE_CXXFLAGS += $$NORMAL_CFLAGS $$NORMAL_CXXFLAGS

  # Not needed - warn_on.prf adds QMAKE_CXXFLAGS_WARN_ON to QMAKE_CXXFLAGS
  #QMAKE_CFLAGS_WARN_ON   += $$NORMAL_CFLAGS
  #QMAKE_CXXFLAGS_WARN_ON += $$NORMAL_CFLAGS $$NORMAL_CXXFLAGS

  QMAKE_CXXFLAGS_WARN_ON += $$USABLE_CXXFLAGS
  #QMAKE_CXXFLAGS_WARN_ON += $$HARD_CXXFLAGS # headers must compile with this, code doesn't need to; needs patched Qt
  #QMAKE_CXXFLAGS_WARN_ON += $$PITA_CXXFLAGS # header would be nice, but it's probably pointless, due to noise from Qt and libstdc++

  CONFIG += hide_symbols
  DEFINES += QT_NO_CAST_FROM_ASCII QT_NO_CAST_TO_ASCII QT_USE_FAST_CONCATENATION QT_USE_FAST_OPERATOR_PLUS QT_STRICT_ITERATORS
}
