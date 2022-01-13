#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main(void) {

  struct timeval start, end;

  gettimeofday(&start, NULL);
  printf("Start seconds: %ld.%ld\n", start.tv_sec, start.tv_usec);

  sleep(30);

  gettimeofday(&end, NULL);

  long unsigned diff = (end.tv_sec - start.tv_sec) + 1e-6*(end.tv_usec - start.tv_usec);
  printf("End seconds: %ld.%ld,\ndiff: %ld\n", end.tv_sec, end.tv_usec, diff);
  

  return 0;
}

