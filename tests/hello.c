#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  printf("Hello world from printf\n");

  /* Open hello.txt for reading */
  FILE *hello = fopen("hello.txt", "r");

  if (hello) {
    /* Iterate through the entire file
     * and print the contents to stdout
     */

    putchar('\n');

    int c;
    while ((c = fgetc(hello)) != EOF) {
      putchar(c);
    }
  }

  printf("argc: %d\n", argc);
  for (int i = 0; i < argc; i++) {
    printf("argv[%d]: %p %s\n", i, (void *)(argv + i), argv[i]);
  }
  return 0;
}
