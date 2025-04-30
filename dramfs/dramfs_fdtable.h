#ifndef DRAMFS_FDTABLE_H
#define DRAMFS_FDTABLE_H

#include <littlefs/lfs.h>

#define DRAMFS_MAX_FDS 128

typedef struct dramfs_fd_entry {
  int used;
  int nonblock;
  lfs_file_t file;
} dramfs_fd_entry_t;

extern dramfs_fd_entry_t *dramfs_fdtable;

void dramfs_init_fdtable(void);

int dramfs_check_fd(int fd);

int dramfs_nonblock_fd(int fd);

int dramfs_reserve_fd(void);

int dramfs_free_fd(int fd);

lfs_file_t *dramfs_get_file(int fd);

#endif  // DRAMFS_FDTABLE_H
