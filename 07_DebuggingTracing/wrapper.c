#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>
#include <errno.h>
#include <config.h>

typedef int (*prev_func_type)(int, const char *, int);

int unlinkat(int dirfd, const char *pathname, int flags) {
    if (strstr(pathname, "FIX") != 0) {
        errno = EPERM;
        return EPERM;
    }
    prev_func_type prev_func = dlsym(RTLD_NEXT, "unlinkat");
    return prev_func(dirfd, pathname, flags);
}