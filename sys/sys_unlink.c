#include <errno.h>

/* Remove a file's directory entry.  */
int _unlink(const char *name) {
  errno = ENOENT;
  return -1;
}
