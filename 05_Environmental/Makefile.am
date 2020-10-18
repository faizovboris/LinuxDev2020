bin_PROGRAMS = RegexpMatcher
RegexpMatcher_SOURCES = main.c pcre_ops.c

gitclean:
	git clean -fd

allclean:
	rm COPYING INSTALL compile config.status

	rm -rf RegexpMatcher configure *~ *.o *.log *.in *.m4 config.h* \
		   Makefile depcomp config.status COPYING INSTALL \
		   compile install-sh missing stamp-h1 autom4te.cache .deps

# autoreconf -fisv