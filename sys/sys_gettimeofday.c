#include <errno.h>
#include <sys/time.h>

#undef errno
extern int errno;

/* Get the current time.  Only relatively correct.  */
int _gettimeofday(struct timeval *tp, void *tzp) {
  errno = EINVAL;
  return -1;
}
