#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>

int elapsed(struct timeval *start, struct timeval *end);
char *to_str_view(int all_msecs);

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Error, command not specific!\n");
    return 1;
  }

  struct timeval start, end;

  gettimeofday(&start, NULL);
  sleep(3);
  gettimeofday(&end, NULL);

  char *view = to_str_view(elapsed(&start, &end));

  printf("%s", view);
  return 0;
}

// creates view of microseconds to seconds
char *to_str_view(int all_msecs) {
  int sec = all_msecs/1e+6;
  int msec = all_msecs%(int)1e+6;

  char *str;
  sprintf(str, "Elapsed time: %u.%u\n", sec, msec);

  return str;
}

// count diff between two timeval
int elapsed(struct timeval *start, struct timeval *end) {
  return ((end->tv_sec - start->tv_sec) * 1000000) + (end->tv_usec - start->tv_usec);
}

