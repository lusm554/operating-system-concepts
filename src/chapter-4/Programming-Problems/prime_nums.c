#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *runner(void *param);

int main(int argc, char **argv) {
  if (argc != 2) return 1;
  char *limit = argv[1];

  pthread_t tid;
  pthread_attr_t attr;

  pthread_attr_init(&attr);  
  pthread_create(&tid, &attr, runner, limit);
  pthread_join(tid, NULL);

  return 0;
}

void *runner(void *param) {
  int limit = atoi(param);

  for (int i = 1; i < limit; i++) {
    int isPrime = 1;

    for (int j = 2; j <= i/2; j++) {
      if (i % j == 0) {
        isPrime = 0;
        break;
      }
    }

    if (isPrime) {
      printf("Prime - %d\n", i);
    }
  }

  pthread_exit(0);
}

