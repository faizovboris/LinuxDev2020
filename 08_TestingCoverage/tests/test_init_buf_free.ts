#include "buf.h"

#test test_init_buf_free
    /* initialization, buf_free() */
    float *a = 0;
    ck_assert_msg(buf_capacity(a) == 0, "capacity init");
    ck_assert_msg(buf_size(a) == 0, "size init");
    buf_push(a, 1.3f);
    ck_assert_msg(buf_size(a) == 1, "size 1");
    ck_assert_msg(a[0] == (float)1.3f, "value");
    buf_clear(a);
    ck_assert_msg(buf_size(a) == 0, "clear");
    ck_assert_msg(a != 0, "clear not-free");
    buf_free(a);
    ck_assert_msg(a == 0, "free");
