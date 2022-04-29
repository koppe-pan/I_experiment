#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void die(char*);

int main(int argc, char ** argv){
  if(argc!=2) die("usage: ./downsample 5 < orig.raw > ds5.raw");
  int ratio = atoi(argv[1]);
  while(1){
    unsigned char data[ratio];
    short n = read(0, data, ratio);
    if ( n==-1 ) die("read");
    if ( n==0 ) break;
    write(1, data, 1);
  }
  return 0;
}

void die(char * s) {
  perror(s);
  exit(1);
}
