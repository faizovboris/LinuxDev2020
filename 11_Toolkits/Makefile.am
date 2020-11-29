bin_PROGRAMS = main
AM_CFLAGS = $(GLIB_CFLAGS) -Wall
LIBS += $(GLIB_LIBS)

test: main
	./main < test.txt

gitclean:
	git clean -fd
	rm -rf *~
