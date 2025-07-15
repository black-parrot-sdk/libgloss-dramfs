#include <errno.h>

/* Establish a new name for an existing file. Minimal implementation */
// TODO: we probably could actually support this easily
int _link(const char *old_name, const char *new_name) {
  errno = ENOSYS;
  return -1;
}
