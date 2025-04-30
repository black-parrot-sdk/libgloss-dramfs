#include <dramfs/dramfs_fdtable.h>
#include <dramfs/dramfs_fs.h>
#include <fcntl.h>
#include <littlefs/bd/lfs_bd.h>
#include <littlefs/lfs.h>
#include <unistd.h>

// Globals used by internal dramfs structures
__attribute__((weak,used)) uint8_t *lfs_ptr = NULL;
__attribute__((weak,used)) lfs_t dramfs_fs = {0};
__attribute__((weak,used)) struct lfs_config dramfs_fs_cfg = {0};

// Init routine for Newlib FS
int dramfs_fs_init(void) {
  // mount the file system if present
  if (lfs_ptr) {
    if (lfs_mount(&dramfs_fs, &dramfs_fs_cfg) < 0) {
      return -1;
    }
  }

  return 0;
}
