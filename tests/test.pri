COTWIDGETS_LIBDIR = $$top_builddir/lib

include( "$$top_srcdir/outdirs.pri" )

QMAKE_RPATHDIR += $$COTWIDGETS_LIBDIR

INCLUDEPATH +=  $$top_srcdir/libcot/keyboards/
DEPENDPATH += $$top_srcdir/libcot/keyboards/


LIBS += -L$$COTWIDGETS_LIBDIR -lcotwidgets
