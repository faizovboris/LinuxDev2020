#include "buf.h"

#test test_buf_grow_trunc
    long *ai = 0;
    /* buf_grow(), buf_trunc() */
    buf_grow(ai, 1000);
    ck_assert_msg(buf_capacity(ai) == 1000, "grow 1000");
    ck_assert_msg(buf_size(ai) == 0, "size 0 (grow)");
    buf_trunc(ai, 100);
    ck_assert_msg(buf_capacity(ai) == 100, "trunc 100");
    buf_free(ai);
