#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *runner(void *param);

int *arr;

int main(int argc, char **argv) {
  if (argc != 2) return 1;
  char *count = argv[1];

  arr = malloc(sizeof(*arr) * atoi(count));

  pthread_t tid;
  pthread_attr_t attr;
  
  pthread_attr_init(&attr);
  pthread_create(&tid, &attr, runner, count);
  pthread_join(tid, NULL);

  printf("Fibonacci sequence:\n");
  for (int i = 0; i < atoi(count); i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  free(arr);

  return 0;
}

void *runner(void *param) {
  int count = atoi(param);
  int a = 0, b = 1;
  // 0 1 1 2 3

  for (int i = 0; i < count; i++) {
    arr[i] = a;

    int temp = a;
    a = b;
    b = temp + b;
  }
  
  pthread_exit(0);
}

