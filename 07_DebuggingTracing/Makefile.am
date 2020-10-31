lib_LTLIBRARIES = libwrapper.la
libwrapper_la_SOURCES = wrapper.c
libwrapper_la_LDFLAGS = avoid-version -module -shared
GENERATES = .libs test_with_FIX.txt test_without_FI_X.txt

check-local:
	./mytests.sh

gitclean:
	git clean -fd

trashclean:
	rm -rf RegexpMatcher configure *~ *.o *.log *.in *.m4 config.h* \
			Makefile depcomp config.status COPYING INSTALL \
			compile install-sh missing stamp-h1 autom4te.cache .deps \
			ltmain.sh libtool config.guess config.sub test-driver

distclean: trashclean clean
	rm -rf $(GENERATES)
