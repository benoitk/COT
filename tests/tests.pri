COTWIDGETS_LIBDIR = $$top_builddir/lib

include( "$$top_srcdir/outdirs.pri" )

QMAKE_RPATHDIR += $$COTWIDGETS_LIBDIR

CONFIG += depend_includepath

INCLUDEPATH *= \
    $$top_srcdir/libcot/keyboards/ \
    $$top_srcdir/libcot/gui/ \
    $$top_srcdir/libcot/gui/widgets \
    $$top_srcdir/libcot/ \
    $$top_srcdir/libcot/automate/variables \
    $$top_srcdir/libcot/automate \
    $$top_srcdir/libcot/automate/com \
    $$top_srcdir/libcot/automate/cycles \
    $$top_srcdir/libcot/automate/actions \
    $$top_srcdir/libcot/automate/units \
    $$top_srcdir/libcot/updater


LIBS += -L$$COTWIDGETS_LIBDIR -lcotwidgets

