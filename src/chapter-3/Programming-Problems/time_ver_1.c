#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>

int elapsed(struct timeval *start, struct timeval *end);
char *to_str_view(int msecs);

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Error, command not specific!\n");
    return 1;
  }

  struct timeval start, end;

  gettimeofday(&start, NULL);
  sleep(1);

  gettimeofday(&end, NULL);

  printf("%u\n", elapsed(&start, &end));
  to_str_view(elapsed(&start, &end));
  
  return 0;
}

char *to_str_view(int msecs) {
  printf("microseconds: %u, s: m/1e+6: %f, ms: %f\n", msecs, msecs/1e+6, msecs%(int)1e+6);
  return &"132"[0];
}

int elapsed(struct timeval *start, struct timeval *end) {
  return ((end->tv_sec - start->tv_sec) * 1000000) + (end->tv_usec - start->tv_usec);
}

