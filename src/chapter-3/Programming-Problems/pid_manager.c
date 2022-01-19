#include <stdio.h>

#define MIN_PID 300
#define MAX_PID 5000
#define SIZE MAX_PID - MIN_PID

int alloc_map(void);
int alloc_pid(void);
void release_pid(int pid);

int bitmap[SIZE];

int main(void) {
  printf("%zu\n", sizeof bitmap);

  alloc_map();
  alloc_pid();

  for (int i = 0; i < 10; i++) {
    printf("bitmap[%d] = %d\n", i, bitmap[i]);
  }

  return 0;
}

int alloc_map(void) {
  for (int i = 0; i < MAX_PID - MIN_PID; i++) {
    bitmap[i] = 0;
  }
  bitmap[0] = 1;
  return 1;
}

int alloc_pid(void) {
  int i = 1;
  while (bitmap[i] != 0) {
    bitmap[i] = 1;
    printf("%d\n", i);
    i++;
  }
  return 1;
}

void release_pid(int pid) {
}

