#include <sys/times.h>
#include <errno.h>

/* Timing info for current process. Minimal implementation */
clock_t _times(struct tms *buf) {
    errno = ENOSYS;
    return -1;
}
