#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void die(char*);

int main(int argc, char ** argv){
  int N = 256;
  char* filename;
  if(argc==2) filename = argv[1];
  else filename = "my_data";

  int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd == -1) die("open");

  unsigned char data[N];
  for(int i = 0; i<N; i++) data[i] = i;
  int write_return = write(fd, data, N);
  if(write_return == -1) die("write");
  close(fd);
  return 0;
}

void die(char * s) {
  perror(s);
  exit(1);
}
