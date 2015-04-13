#ifndef COTGLOBAL_H
#define COTGLOBAL_H

#include <qglobal.h>

# ifdef COTWIDGETS_STATICLIB
#  undef COTWIDGETS_SHAREDLIB
#  define COTWIDGETS_EXPORT
# else
#  ifdef COTWIDGETS_BUILD_COTWIDGETS_LIB
#   define COTWIDGETS_EXPORT Q_DECL_EXPORT
#  else
#   define COTWIDGETS_EXPORT Q_DECL_IMPORT
#  endif
# endif

#endif /* COTGLOBAL_H */

