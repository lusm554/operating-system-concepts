#include <stdio.h>

#define MIN_PID 300
#define MAX_PID 5000
#define SIZE MAX_PID - MIN_PID

int main(void) {
  int bitmap[SIZE];

  printf("%zu\n", sizeof bitmap);

  for (int i = 0; i < (MAX_PID - MIN_PID); i++) {
    bitmap[i] = 1;
  }

  return 0;
}

int alloc_map(void) {}
int allo_pid(void) {}
void release_pid(int pid) {}

