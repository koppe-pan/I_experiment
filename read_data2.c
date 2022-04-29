#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void die(char*);

int main(int argc, char ** argv){
  char* filename;
  if(argc!=2) die("usage: ./read_data2 sin.raw");
  filename = argv[1];

  int fd = open(filename, O_RDONLY, 0644);

  int N = 2;
  short data[1];
  int cur = 0;
  while (1) {
    int n = read(fd, data, N);
    if (n == -1) die("read");
    if (n == 0) break; /* 無事にファイルの終わりに達した */
    printf("%d %d\n", cur, data[0]);
    cur++;
  }
  close(fd);
  return 0;
}

void die(char * s) {
  perror(s);
  exit(1);
}
