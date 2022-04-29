#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char ** argv){
  int N = 256;
  char* filename;
  if(argc==2) filename = argv[1];
  else filename = "my_data";

  int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  unsigned char data[N];
  for(int i = 0; i<N; i++) data[i] = i;
  write(fd, data, N);
  close(fd);
  return 0;
}
