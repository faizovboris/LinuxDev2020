#include "buf.h"

#test test_buf_push_indexing
    /* buf_push(), [] operator */
    long *ai = 0;
    for (int i = 0; i < 10000; i++)
        buf_push(ai, i);
    ck_assert_msg(buf_size(ai) == 10000, "size 10000");
    int match = 0;
    for (int i = 0; i < (int)(buf_size(ai)); i++)
        match += ai[i] == i;
    ck_assert_msg(match == 10000, "match 10000");
    buf_free(ai);
