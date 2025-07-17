#include <stddef.h>
#include <errno.h>

extern char _end[];
static char *curbrk = _end;

void *_sbrk(ptrdiff_t incr)
{
    extern char __heap_end[];
    char *newbrk;
    char *oldbrk;

    oldbrk = curbrk;
    newbrk = oldbrk + incr;
    if ((newbrk < _end) || (newbrk >= __heap_end)) {
        errno = ENOMEM;
        return (void *)(-1);
    }

    curbrk = newbrk;
    return oldbrk;
}

