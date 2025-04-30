#include <dramfs/dramfs_intf.h>
#include <unistd.h>

/* Exit a program without cleaning up files.  */
void _exit(int exit_status) {
  // close stdio
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  dramfs_exit(exit_status);
  __builtin_unreachable();
}
