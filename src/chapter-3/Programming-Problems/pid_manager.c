#include <stdio.h>
#include <stdlib.h>

#define MIN_PID 300
#define MAX_PID 5000
#define SIZE MAX_PID - MIN_PID

int alloc_map(void);
int alloc_pid(void);
void release_pid(int pid);

int bitmap[SIZE] = {0};

int main(void) {
  alloc_map();

  printf("%zu\n", sizeof bitmap);

  for (int i = 0; i < 5; i++) {
    int t = alloc_pid();
  }

  for (int i = 0; i < 6; i++) {
    printf("bitmap[%d] = %d\n", i, bitmap[i]);
  }

  for (int i = 0; i < 5; i++) {
    release_pid(MIN_PID + i);
  }

  printf("\n");
  for (int i = 0; i < 6; i++) {
    printf("bitmap[%d] = %d\n", i, bitmap[i]);
  }

  return 0;
}

// TODO: fix allocation of map 
int alloc_map(void) {
  return 1;
}

int alloc_pid(void) {
  for (int i = 0; i < SIZE; i++) {
    if (bitmap[i] == 0) {
      bitmap[i] = MIN_PID + i;
      return MIN_PID + i; 
    }
  }

  return -1;
}

void release_pid(int pid) {
  if (!(pid >= MIN_PID & pid <= MAX_PID)) return;
  bitmap[pid - MIN_PID] = 0;
}

