#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

void die(char*);

int main(int argc, char ** argv){
  if(argc!=3) die("usage: ./client_recv IP port");

  //int channel = 1;
  char* ip = argv[1];
  int port = atoi(argv[2]);


  int s = socket(PF_INET, SOCK_STREAM, 0);
  if(s==-1) die("socket(PF_INET, SOCK_STREAM, 0)");

  struct sockaddr_in addr;
  addr.sin_family = AF_INET; /* これはIPv4 のアドレスです */
  if(inet_aton(ip, &addr.sin_addr)==0) die("inet_aton"); /* IP アドレスは...です */
  addr.sin_port = htons(port); /* ポートは...です */
  if(connect(s, (struct sockaddr *)&addr, sizeof(addr))==-1) die("connect");


  int N = 1;
  unsigned char data[N];
  while (1) {
    int n = read(s, data, N);
    if (n == -1) die("read");
    if (n == 0) break;
    if(write(1, data, n) == -1) die("write");
  }
  close(s);
  return 0;
}

void die(char * s) {
  perror(s);
  exit(1);
}
