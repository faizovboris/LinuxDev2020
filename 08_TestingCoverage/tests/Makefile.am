TESTS = test_init_buf_free test_null_ptr test_buf_push_indexing test_buf_grow_trunc test_buf_pop
check_PROGRAMS = test_init_buf_free test_null_ptr test_buf_push_indexing test_buf_grow_trunc test_buf_pop

CFLAGS = -I$(top_builddir)/src @CHECK_CFLAGS@
LDADD = $(top_builddir)/src/libbuf.la @CHECK_LIBS@

.ts.c:
	checkmk $< > $@
