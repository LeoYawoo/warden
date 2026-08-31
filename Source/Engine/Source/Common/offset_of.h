#pragma once

#include <cstddef>

//#ifdef BROKEN_OFFSETOF_MACRO
//#undef offsetof
//#define offsetof(type, member)   ((size_t)((char *)&(*(type *)0).member - \
//                                           (char *)&(*(type *)0)))
//#endif /* BROKEN_OFFSETOF_MACRO */


#if defined(WIN32) && defined(_MSC_VER) && _MSC_VER >= 1910
#  define STRUCT_OFFSET(s, m)  (size_t)(&(((s *)0)->m))
#else
#  include <stddef.h>
#  define STRUCT_OFFSET(s,m)  offsetof(s,m)
#endif