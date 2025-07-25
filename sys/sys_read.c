#include <dramfs/dramfs_fdtable.h>
#include <dramfs/dramfs_fs.h>
#include <dramfs/dramfs_intf.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

/* Read from a file.  */
ssize_t _read(int fd, void *ptr, size_t len) {
  if (fd == STDIN_FILENO) {
    uint8_t *data = (uint8_t *)ptr;

    // Return early on len == 0
    if (len == 0) return (ssize_t)0;

    int ch;
    if (dramfs_nonblock_fd(fd) == 0) {
      // Block to read just 1 character to start
      while ((ch = dramfs_getchar()) == -1);
    } else {
      // Read the first character, and return immediately if it's EOF
      if ((ch = dramfs_getchar()) == -1) return (ssize_t)0;
    }

    // Keep reading until new
    int i = 0;
    do {
      data[i++] = ch;
      if (i == len) break;
    } while ((ch = dramfs_getchar()) != -1);

    return (ssize_t)i;
  }

  if (dramfs_check_fd(fd) < 0) {
    errno = EBADF;
    return -1;
  }

  lfs_file_t *fptr = dramfs_get_file(fd);
  return (ssize_t)lfs_file_read(&dramfs_fs, fptr, ptr, (lfs_size_t)len);
}
