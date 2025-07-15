#include <dramfs/dramfs_fdtable.h>
#include <dramfs/dramfs_fs.h>
#include <dramfs/dramfs_intf.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

/* Write to a file.  */
ssize_t _write(int fd, const void *ptr, size_t len) {
  // write to console if it's stdout
  if (fd == STDOUT_FILENO || fd == STDERR_FILENO) {
    for (int i = 0; i < len; i++) {
      char *cp = (char *)ptr;
      dramfs_sendchar(cp[i]);
    }
    return len;
  }

  if (dramfs_check_fd(fd) < 0) {
    errno = EBADF;
    return -1;
  }

  lfs_file_t *fptr = dramfs_get_file(fd);
  return (ssize_t)lfs_file_write(&dramfs_fs, fptr, ptr, (lfs_size_t)len);
}
