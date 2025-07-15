#include <dramfs/dramfs_fdtable.h>
#include <dramfs/dramfs_fs.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

int _fstat(int file, struct stat *st) {
  if (file == STDOUT_FILENO || file == STDERR_FILENO) {
    st->st_mode = S_IFCHR;
    return 0;
  }

  if (file == STDIN_FILENO) {
    st->st_mode = S_IFCHR;
    return 0;
  }

  if (dramfs_check_fd(file) < 0) {
    errno = EBADF;
    return -1;
  }

  lfs_file_t *fptr;
  fptr = dramfs_get_file(file);

  st->st_mode = S_IFREG;
  st->st_size = (off_t)fptr->size;
  st->st_blksize = (blksize_t)dramfs_fs_cfg.block_size;
  st->st_blocks = (blkcnt_t)dramfs_fs_cfg.block_count;
  return 0;
}
