#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// This data is shared by the thread(s)
int sum;
// Threads call this function
void *runner(void *param);

int main(int argc, char **argv) {
  char *number_to_sum = argv[1];
  pthread_t tid; // the thread identifier
  pthread_attr_t attr; // set of thread attributes
  
  // Set the default attributes of the thread
  pthread_attr_init(&attr);
  // Create the thread
  pthread_create(&tid, &attr, runner, number_to_sum);
  // Wait for the thread to exit
  pthread_join(tid, NULL);

  printf("sum = %d\n", sum);
  return 0;  
}

// The thread will execute in this function
void *runner(void *param) {
  int i, upper = atoi(param);
  sum = 0;

  for (i = 1; i <= upper; i++) {
    sum += i;
  }
  
  pthread_exit(0);
} 

