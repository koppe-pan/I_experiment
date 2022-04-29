#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.141592

// usage: gcc doremi.c -lm; ./a.out 10000 | play -t raw -b 16 -c 1 -e s -r 44100 -

void die(char*);
void beep(double, double);

int main(int argc, char ** argv){
  if(argc!=2) die("usage: ./doremi A");
  double A = atof(argv[1]);
  int f = 440;
  int tones[8] = {-9, -7, -5, -4, -2, 0, 2, 3};
  for(int i = 0; i<8; i++){
    beep(A, f*pow(2.0, tones[i]/12.0));
  }
  return 0;
}

void beep(double A, double f){
  int n = 13230;
  int sampling_rate = 44100;
  double dt = 1/(double)sampling_rate;

  short data[n];
  for (int i = 0; i < n; i++){
    data[i] = A * sin(2*PI*f*i*dt);
  }

  int write_return = write(1, data, sizeof(short)*n);
  if(write_return == -1) die("write");
}

void die(char * s) {
  perror(s);
  exit(1);
}
