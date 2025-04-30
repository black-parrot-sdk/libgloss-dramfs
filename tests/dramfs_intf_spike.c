
#include <stdint.h>
#include <unistd.h>

#define SYS_read 63
#define SYS_write 64
#define SYS_exit 93

volatile uint64_t tohost __attribute__((section(".htif"), aligned(64)));
volatile uint64_t fromhost __attribute__((section(".htif"), aligned(64)));

static uintptr_t syscall(uintptr_t which, uint64_t arg0, uint64_t arg1,
                         uint64_t arg2) {
  volatile uint64_t magic_mem[8] __attribute__((aligned(64)));
  magic_mem[0] = which;
  magic_mem[1] = arg0;
  magic_mem[2] = arg1;
  magic_mem[3] = arg2;
  __sync_synchronize();

  tohost = (uintptr_t)magic_mem;
  while (fromhost == 0);
  fromhost = 0;

  __sync_synchronize();
  return magic_mem[0];
}

void dramfs_exit(int code) {
  tohost = (code << 1) | 1;
  while (1);
}

void dramfs_sendchar(int ch) {
  static __thread char buf[64] __attribute__((aligned(64)));
  static __thread int buflen = 0;

  buf[buflen++] = ch;

  if (ch == '\n' || buflen == sizeof(buf)) {
    syscall(SYS_write, 1, (uintptr_t)buf, buflen);
    buflen = 0;
  }
}

int dramfs_getchar(void) { return -1; }
