#include <dramfs/dramfs_fdtable.h>
#include <dramfs/dramfs_fs.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

/* Set position in a file.  */
off_t _lseek(int file, off_t ptr, int dir) {
  if (file == STDIN_FILENO || file == STDOUT_FILENO || file == STDERR_FILENO) {
    return EBADF;
  }

  if (dramfs_check_fd(file) < 0) {
    return EBADF;
  }

  lfs_file_t *fptr = dramfs_get_file(file);
  return lfs_file_seek(&dramfs_fs, fptr, ptr, dir);
}
