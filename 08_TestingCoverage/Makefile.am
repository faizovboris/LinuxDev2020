SUBDIRS = src tests

gitclean: maintainer-clean
	git clean -fd

gcov:	check
	$(MAKE) -C src gcov
