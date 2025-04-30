
// Default implementation of dramfs hooks
//
void __attribute__((weak)) dramfs_exit(int code) { while(1); }

void __attribute__((weak)) dramfs_sendchar(int ch) { return; }

int __attribute__((weak)) dramfs_getchar(void) { return -1; }

