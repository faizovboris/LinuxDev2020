#ifndef PCRE2_CODE_UNIT_WIDTH
#define PCRE2_CODE_UNIT_WIDTH 8
#endif

#include <stdio.h>
#include <string.h>
#include <pcre2.h>
#include <config.h>
#include "pcre_ops.h"

#define MAX_ERROR_MESSAGE_LEN 356

struct PcreResult processString(char* pattern_str, char *subject_str, int is_use_ucp) {
    struct PcreResult ans;
    ans.is_error = 0;
    ans.answer = malloc(MAX_ERROR_MESSAGE_LEN * sizeof(*ans.answer));

    PCRE2_SPTR pattern = (PCRE2_SPTR)pattern_str;
    PCRE2_SPTR subject = (PCRE2_SPTR)subject_str;
    PCRE2_SIZE subject_length = (PCRE2_SIZE)strlen((char *)subject);

    PCRE2_SIZE erroffs;
    int errnum;
    pcre2_code *re = NULL;
    if (is_use_ucp) {
        re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, PCRE2_UCP, &errnum, &erroffs, NULL);
    } else {
        re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, 0, &errnum, &erroffs, NULL);
    }

    if (re == NULL) {
        ans.is_error = 1;
        PCRE2_UCHAR buffer[256];
        pcre2_get_error_message(errnum, buffer, sizeof(buffer));
        snprintf(ans.answer,
            MAX_ERROR_MESSAGE_LEN,
            "PCRE2 compilation failed at offset %d: %s\n", (int)erroffs, buffer);
        return ans;
    }

    pcre2_match_data *match_data = pcre2_match_data_create_from_pattern(re, NULL);
    int rc = pcre2_match(re, subject, subject_length, 0, 0, match_data, NULL);

    if (rc < 0) {
        ans.is_error = 1;
        switch(rc) {
        case PCRE2_ERROR_NOMATCH:
            snprintf(ans.answer, MAX_ERROR_MESSAGE_LEN, "No match\n");
            break;
        default:
            snprintf(ans.answer, MAX_ERROR_MESSAGE_LEN, "Matching error %d\n", rc);
            break;
        }
        pcre2_match_data_free(match_data);
        pcre2_code_free(re);
        return ans;
    }

    PCRE2_SIZE *ovector = pcre2_get_ovector_pointer(match_data);

    size_t cur_ans_pos = 0, cur_ans_capacity = MAX_ERROR_MESSAGE_LEN;
    for (int i = 0; i < rc; i++) {
        size_t try_write = 0;
        try_write = snprintf(ans.answer + cur_ans_pos,
                             cur_ans_capacity - cur_ans_pos,
                             "%2ld: %.*s\n", ovector[2*i], 
                                 (int)(ovector[2*i+1] - ovector[2*i]),
                                 subject + ovector[2*i]);
        while (try_write > cur_ans_capacity - cur_ans_pos) {
            cur_ans_capacity <<= 1;
            ans.answer = realloc(ans.answer, cur_ans_capacity * sizeof(*ans.answer));
            try_write = snprintf(ans.answer + cur_ans_pos,
                                 cur_ans_capacity - cur_ans_pos,
                                 "%2ld: %.*s\n", ovector[2*i], 
                                     (int)(ovector[2*i+1] - ovector[2*i]),
                                     subject + ovector[2*i]);
        }
        cur_ans_pos += try_write;
    }

    pcre2_match_data_free(match_data);
    pcre2_code_free(re);
    return ans;
};