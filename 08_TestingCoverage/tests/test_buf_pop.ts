#include "buf.h"

#test test_buf_pop
    float *a = 0;
    /* buf_pop() */
    buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);
    ck_assert_msg(buf_size(a) == 4, "size 4");
    ck_assert_msg(buf_pop(a) == (float)1.4f, "pop 3");
    buf_trunc(a, 3);
    ck_assert_msg(buf_size(a) == 3, "size 3");
    ck_assert_msg(buf_pop(a) == (float)1.3f, "pop 2");
    ck_assert_msg(buf_pop(a) == (float)1.2f, "pop 1");
    ck_assert_msg(buf_pop(a) == (float)1.1f, "pop 0");
    ck_assert_msg(buf_size(a) == 0, "size 0 (pop)");
    buf_free(a);
