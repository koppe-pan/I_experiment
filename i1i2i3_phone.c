#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

void die(char*);

int main(int argc, char ** argv){
  time_t t_ini = time(NULL);
  int port;
  int s;
  struct sockaddr_in addr;

  switch(argc){
    case 3:
      // client side
      char* ip = argv[1];
      port = atoi(argv[2]);


      s = socket(PF_INET, SOCK_STREAM, 0);
      if(s==-1) die("socket(PF_INET, SOCK_STREAM, 0)");

      addr.sin_family = AF_INET; /* これはIPv4 のアドレスです */
      if(inet_aton(ip, &addr.sin_addr)==0) die("inet_aton"); /* IP アドレスは...です */
      addr.sin_port = htons(port); /* ポートは...です */
      if(connect(s, (struct sockaddr *)&addr, sizeof(addr))==-1) die("connect");
      break;

    case 2:
      // server side
      port = atoi(argv[1]);

      int ss = socket(PF_INET, SOCK_STREAM, 0);
      if(ss==-1) die("socket(PF_INET, SOCK_STREAM, 0)");

      addr.sin_family = AF_INET; /* このアドレスはIPv4 アドレスです */
      addr.sin_port = htons(port); /* ポート...で待ち受けしたいです */
      addr.sin_addr.s_addr = INADDR_ANY; /* どのIP アドレスでも待ち受けしたいです */
      bind(ss, (struct sockaddr *)&addr, sizeof(addr));
      listen(ss, 10);

      struct sockaddr_in client_addr;
      socklen_t len = sizeof(struct sockaddr_in);

      s = accept(ss, (struct sockaddr *)&client_addr, &len);
      if(s==-1) die("connect");
      close(ss);

      int N2 = 22050;
      unsigned char* data2 = malloc(sizeof(char)*N2);
      time_t t = time(NULL);
      for(int i = 0; i<(t-t_ini+1)*4; i++)
      {
        int n = read(STDIN_FILENO, data2, N2);
        if (n == -1) die("read");
      }
      free(data2);

      break;

    default: die("usage for server: ./i1i2i3_phone port\nusage for client: ./i1i2i3_phone ip_address port\n ");
  }

  int N = 1000;
  unsigned char data[N];
  while (1) {
    int n = read(STDIN_FILENO, data, N);
    if (n == -1) die("read");
    if (n == 0) break;
    if(write(s, data, n) == -1) die("write");

    n = read(s, data, N);
    if (n == -1) die("read");
    if (n == 0) break;
    if(write(STDOUT_FILENO, data, n) == -1) die("write");
  }
  close(s);
  return 0;
}

void die(char * s) {
  perror(s);
  exit(1);
}
