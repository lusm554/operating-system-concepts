#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
  pid_t pid;
  pid = fork();

  if (pid < 0) { // error
    return 1;
  }

  if (pid == 0) { // child process
    exit(0);
  }

  if (pid > 0) { // parent process
    // sleep 20 seconds
    time_t end_time = time(NULL) + 20;
    while(time(NULL) < end_time);

    // or just sleep(20);
  }

  return 0;
}

