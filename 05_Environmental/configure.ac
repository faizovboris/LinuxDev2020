#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([RegexpMatcher], [1.0.0], [faizovboris])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([main.c])
AC_CONFIG_SRCDIR([pcre_ops.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lncursesw':
AC_CHECK_LIB([ncursesw], [initscr], [], [AC_MSG_ERROR([Curses is needed])])

AC_CHECK_LIB([pcre2-8], [pcre2_code_free_8], [], [AC_MSG_ERROR([Pcre is needed])])

# Checks for header files.
AC_CHECK_HEADERS([locale.h], [], [AC_MSG_ERROR([Can't find locale.h])])

AC_CHECK_HEADERS([stdio.h], [], [AC_MSG_ERROR([Can't find stdio.h])])

AC_CHECK_HEADERS([stdlib.h], [], [AC_MSG_ERROR([Can't find stdlib.h])])

AC_CHECK_HEADERS([string.h], [], [AC_MSG_ERROR([Can't find string.h])])

AC_CHECK_HEADERS([ncurses.h], [], [AC_MSG_ERROR([Can't find ncurses.h])])

AC_CHECK_HEADERS([pcre2.h], [], [AC_MSG_ERROR([Can't find pcre2.h])],
    [#define PCRE2_CODE_UNIT_WIDTH 0
     #include <pcre2.h>
    ])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC

AC_ARG_ENABLE([UTF],
	AS_HELP_STRING([--without-UTF], [Turn off UTF option]))
	
AS_IF([test "x$with_UTF" != "xno"], [
	AC_DEFINE(UTF,[],[Have UTF turned on])
])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
