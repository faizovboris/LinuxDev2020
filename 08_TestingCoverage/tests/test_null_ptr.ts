#include "buf.h"

#test test_null_ptr
    float *a = 0;
    /* Clearing an NULL pointer is a no-op */
    buf_clear(a);
    ck_assert_msg(buf_size(a) == 0, "clear empty");
    ck_assert_msg(a == 0, "clear no-op");
