#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([ScriptingText], [1.0.0], [faizovboris])
AM_INIT_AUTOMAKE()
AC_CONFIG_SRCDIR([prog.c])
AC_CONFIG_SRCDIR([fun.c])
AC_CONFIG_SRCDIR([const.c])
AC_CONFIG_SRCDIR([outlib.h])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([insver.sh])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdio.h], [], [AC_MSG_ERROR([Can't find stdio.h])])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

sh insver.sh
