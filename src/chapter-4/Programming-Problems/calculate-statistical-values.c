#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *get_avg(void *raw_args);
void *get_max(void *raw_args);
void *get_min(void *raw_args);

int MAX;
int MIN;
int AVG;

struct arg_struct {
  int *arr;
  int len;
} *args;

int main() {
  int test[] = {1, 2, 3, 4, 5};
  args = malloc((int)sizeof(struct arg_struct));

  args->arr = test;
  args->len = (int)(sizeof(test)/sizeof(int));

  for (int i = 0; i < 3; i++) {
    pthread_t tid; // the thread identifier
    pthread_attr_t attr; // set of thread attributes

    pthread_attr_init(&attr); // set the default attributes of the thread
  
    switch (i) {
      case 0:
        pthread_create(&tid, &attr, get_avg, args); // create the thread
        break;
      case 1:
        pthread_create(&tid, &attr, get_max, args); // create the thread
        break;
      case 2:
        pthread_create(&tid, &attr, get_min, args); // create the thread
        break;
    }

    pthread_join(tid, NULL); // wait for the thread to exit
  }


  printf("avg: %d, max: %d, min: %d\n", AVG, MIN, MAX);
  free(args);
  return 0;
}

void *get_avg(void *raw_args) {
  struct arg_struct *args = raw_args;

  AVG = 0;
  int sum = 0;

  for (int i = 0; i < args->len; i++) {
    sum += args->arr[i];
  }
  
  AVG = sum / args->len;
  pthread_exit(0);
}

void *get_max(void *raw_args) {
  struct arg_struct *args = raw_args;
  int m = args->arr[0];
  
  for (int i = 0; i < args->len; i++) {
    if (args->arr[i] > m) {
      m = args->arr[i];
    }
  }

  MIN = m;
  pthread_exit(0);
}
    
void *get_min(void *raw_args) {
  struct arg_struct *args = raw_args;
   int m = args->arr[0];
  
  for (int i = 0; i < args->len; i++) {
    if (args->arr[i] < m) {
      m = args->arr[i];
    }
  }

  MAX = m;
  pthread_exit(0);
}

