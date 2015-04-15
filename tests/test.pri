COTWIDGETS_LIBDIR = $$top_builddir/lib

include( "$$top_srcdir/outdirs.pri" )

QMAKE_RPATHDIR += $$COTWIDGETS_LIBDIR

INCLUDEPATH +=  $$top_srcdir/libcot/keyboards/ $$top_srcdir/libcot/gui/ $$top_srcdir/libcot/
DEPENDPATH += $$top_srcdir/libcot/keyboards/ $$top_srcdir/libcot/gui/  $$top_srcdir/libcot/


LIBS += -L$$COTWIDGETS_LIBDIR -lcotwidgets
