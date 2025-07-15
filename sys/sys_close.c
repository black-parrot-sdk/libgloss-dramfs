#include <dramfs/dramfs_fdtable.h>
#include <dramfs/dramfs_fs.h>
#include <unistd.h>
#include <errno.h>

/* Close a file.  */
int _close(int fd) {
  if (fd == STDIN_FILENO || fd == STDOUT_FILENO || fd == STDERR_FILENO) {
    return 0;
  }

  if (dramfs_check_fd(fd) < 0) {
    errno = EBADF;
    return -1;
  }

  if (dramfs_free_fd(fd) < 0) {
    errno = EBADF;
    return -1;
  }

  return 0;
}
