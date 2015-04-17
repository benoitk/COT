#ifndef COTGLOBAL_H
#define COTGLOBAL_H

#include <qglobal.h>

# ifdef LIBCOT_STATIC_BUILD
#  define LIBCOT_EXPORT
# else
#  ifdef LIBCOT_BUILD
#   define LIBCOT_EXPORT Q_DECL_EXPORT
#  else
#   define LIBCOT_EXPORT Q_DECL_IMPORT
#  endif
# endif

#endif /* COTGLOBAL_H */

