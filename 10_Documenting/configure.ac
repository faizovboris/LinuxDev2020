#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([numberGuesser], [1.0], [faizovboris])
AM_INIT_AUTOMAKE
DX_INIT_DOXYGEN(guesser)
AC_CONFIG_SRCDIR([main.c])
AC_CONFIG_SRCDIR([roman.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([libintl.h locale.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([setlocale])

AC_CONFIG_FILES([Makefile
				 Doxyfile
				 guesser.md
				 roman.md])
AC_OUTPUT
