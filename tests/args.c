
#include <stddef.h>

#define MY_ARGC 2

const char *__argv[MY_ARGC + 1]
    __attribute__((used)) = {"custom1", "custom2", NULL};
const long long int __argc = MY_ARGC;
