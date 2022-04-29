#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.141592

void die(char*);

int main(int argc, char ** argv){
  if(argc!=4) die("usage: ./sin A f n");

  //int channel = 1;
  double A = atof(argv[1]);
  double f = atof(argv[2]);
  int n = atoi(argv[3]);
  int sampling_rate = 44100;
  double dt = 1/(double)sampling_rate;

  short data[n];
  for (int i = 0; i < n; i++){
    data[i] = A * sin(2*PI*f*i*dt);
  }

  write(1, data, sizeof(short)*n);
  //for(int i = 0; i<100; i++) printf("%d\n", (short)data[i]);
  return 0;
}

void die(char * s) {
  perror(s);
  exit(1);
}
