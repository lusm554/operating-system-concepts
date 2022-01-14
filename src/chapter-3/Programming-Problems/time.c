#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main(void) {

  struct timeval start, end;

  gettimeofday(&start, NULL);
  printf("Waiting %u seconds\n", 5);
    
  sleep(5);

  gettimeofday(&end, NULL);

  int elapsed = ((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec);
  printf("elapsed: %u\n", elapsed);

  return 0;
}

