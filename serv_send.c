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
  if(argc!=2) die("usage: ./serv_send port");

  int port = atoi(argv[1]);

  int ss = socket(PF_INET, SOCK_STREAM, 0);
  if(ss==-1) die("socket(PF_INET, SOCK_STREAM, 0)");

  struct sockaddr_in addr; /* 最終的にbind に渡すアドレス情報 */
  addr.sin_family = AF_INET; /* このアドレスはIPv4 アドレスです */
  addr.sin_port = htons(port); /* ポート...で待ち受けしたいです */
  addr.sin_addr.s_addr = INADDR_ANY; /* どのIP アドレスでも待ち受けしたいです */
  bind(ss, (struct sockaddr *)&addr, sizeof(addr));
  listen(ss, 10);

  struct sockaddr_in client_addr;
  socklen_t len = sizeof(struct sockaddr_in);
  int s = accept(ss, (struct sockaddr *)&client_addr, &len);
  if(s==-1) die("connect");
  close(ss);

  int N = 1000;
  unsigned char data[N];
  while (1) {
    int n = read(0, data, N);
    if (n == -1) die("read");
    if (n == 0) break;
    if(write(s, data, n) == -1) die("write");
  }
  close(s);
  return 0;
}

void die(char * s) {
  perror(s);
  exit(1);
}
