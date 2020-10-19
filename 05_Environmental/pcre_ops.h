struct PcreResult {
    char *answer;
};

struct PcreResult processString(char* pattern_str, char *subject_str, int is_use_ucp);