#include <dramfs/dramfs_fdtable.h>
#include <dramfs/dramfs_fs.h>
#include <unistd.h>

dramfs_fd_entry_t *dramfs_fdtable __attribute__((weak,used)) = NULL;

int dramfs_check_fd(int fd) {
  if (fd == STDIN_FILENO || fd == STDOUT_FILENO || fd == STDERR_FILENO) {
    return 0;
  }

  if (fd < 0 || fd >= DRAMFS_MAX_FDS || !dramfs_fdtable ||
      !dramfs_fdtable[fd].used) {
    return -1;
  }

  return 0;
}

int dramfs_nonblock_fd(int fd) {
  if (dramfs_fdtable[fd].nonblock == 1) {
    return 1;
  }

  return 0;
}

int dramfs_reserve_fd(void) {
  if (!dramfs_fdtable) {
    return -1;
  }

  for (int fd = STDERR_FILENO + 1; fd < DRAMFS_MAX_FDS; fd++) {
    if (dramfs_fdtable[fd].used == 0) {
      dramfs_fdtable[fd].used = 1;
      return fd;
    }
  }

  return -1;
}

int dramfs_free_fd(int fd) {
  if (!dramfs_fdtable) {
    return -1;
  }

  if (dramfs_fdtable[fd].used == 1) {
    lfs_file_t *fptr = dramfs_get_file(fd);
    dramfs_fdtable[fd].used = 0;
    return lfs_file_close(&dramfs_fs, fptr);
  } else {
    return 0;
  }
}

lfs_file_t *dramfs_get_file(int fd) {
  if (!dramfs_fdtable) {
    return NULL;
  }
  return &dramfs_fdtable[fd].file;
}
