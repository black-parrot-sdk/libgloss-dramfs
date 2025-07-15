/* Query whether output stream is a terminal. For consistency with the
   other minimal implementations, which only support output to stdout,
   this minimal implementation is suggested by the newlib docs.  */

#include <unistd.h>

int _isatty(int file) {
    return (file == STDOUT_FILENO || file == STDERR_FILENO);
}
