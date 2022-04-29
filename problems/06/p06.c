/*
 * p06.c
 */

/*
 * usage:
 *
 *   ./a.out
 *
 * Intented behavior:
 * It should print the content of this file.
 *
 */

#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
  int fd = open("p06.c", O_RDONLY);
  if (fd == NULL) {
    printf("read error\n");
  }

  char buf[100];
  while (1) {
    int n = read(fd, buf, 100);
    if (n == 0) break;
    write(1, buf, n);
  }
  return 0;
}
