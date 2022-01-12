#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int value = 5;

int main(void) {
	pid_t pid;
  pid = fork();

  printf("pid - %u\n", pid);

  if (pid == 0) { // child
    value += 15;
    return 0;
  }

  if (pid > 0) { // parent
    wait(NULL);
    printf("num: %u\n", value);
    return 0;
  }

}
