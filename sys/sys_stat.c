#include <dramfs/dramfs_fs.h>
#include <errno.h>
#include <sys/stat.h>

/* Status of a file (by name).  */

int _stat(const char *file, struct stat *st) {
  struct lfs_info finfo;

  if (lfs_stat(&dramfs_fs, file, &finfo) < 0) {
    errno = ENOSYS;
    return -1;
  } else {
    st->st_mode = S_IFREG;
    st->st_size = (off_t)finfo.size;
    st->st_blksize = (blksize_t)dramfs_fs_cfg.block_size;
    st->st_blocks = (blkcnt_t)dramfs_fs_cfg.block_count;
    return 0;
  }
}
