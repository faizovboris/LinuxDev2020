#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([DebuggingTracing], [1.0.0], [faizovboris])
AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AM_PROG_LIBTOOL

# Checks for libraries.
AC_CHECK_LIB([dl], [dlopen], [], [AC_MSG_ERROR([dlfcn is needed])])

# Checks for header files.
AC_CHECK_HEADERS([dlfcn.h], [], [AC_MSG_ERROR([Can't find dlfcn.h])])

AC_CHECK_HEADERS([string.h], [], [AC_MSG_ERROR([Can't find string.h])])

AC_CHECK_HEADERS([errno.h], [], [AC_MSG_ERROR([Can't find errno.h])])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([strstr])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
