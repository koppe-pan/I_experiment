#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

void die(char*);

int main(int argc, char ** argv){
  if(argc!=3) die("usage: ./client_send_recv_udp IP port");

  //int channel = 1;
  char* ip = argv[1];
  int port = atoi(argv[2]);


  int s = socket(AF_INET, SOCK_DGRAM, 0);
  if(s==-1) die("socket(AF_INET, SOCK_DGRAM, 0)");

  struct sockaddr_in addr;
  addr.sin_family = AF_INET; /* これはIPv4 のアドレスです */
  if(inet_aton(ip, &addr.sin_addr)==0) die("inet_aton"); /* IP アドレスは...です */
  addr.sin_port = htons(port); /* ポートは...です */
  if(connect(s, (struct sockaddr *)&addr, sizeof(addr))==-1) die("connect");


  int N = 1000;
  unsigned char data[N];
  unsigned char EOD[N];
  memset(data, 0, sizeof(data));
  memset(EOD, 1, sizeof(EOD));

  for(int i=0; i<50; i++){
    int n = read(0, data, N);
    if (n == -1) die("read from stdin");
    if (n == 0) break;
    if (strcmp(data, EOD)==0) break;
    if(write(s, data, n) == -1) die("write to socket");
  }
  if(write(s, EOD, N) == -1) die("write EOD");

  while (1) {
    int n = read(s, data, N);
    if (n == -1) die("read from socket");
    if (n == 0) break;
    if (strcmp(data, EOD)==0) break;
    if(write(1, data, n) == -1) die("write to stdout");
  }
  close(s);
  return 0;
}

void die(char * s) {
  perror(s);
  exit(1);
}
