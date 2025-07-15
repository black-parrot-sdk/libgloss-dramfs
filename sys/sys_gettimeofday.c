#include <errno.h>
#include <sys/time.h>

/* Get the current time.  Only relatively correct.  */
int _gettimeofday(struct timeval *tp, void *tzp) {
  errno = ENOSYS;
  return -1;
}
