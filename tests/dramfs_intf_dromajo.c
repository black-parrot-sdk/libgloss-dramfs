
void dramfs_exit(int code) {
  char *exit_addr = (char *)0x102000;
  *exit_addr = code;
}

void dramfs_sendchar(int ch) {
  char *putc_addr = (char *)0x101000;
  *putc_addr = (char)ch;
}

int dramfs_getchar(void) { return -1; }
