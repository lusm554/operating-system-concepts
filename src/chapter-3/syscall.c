#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
  pid_t pid;
  
  /* fork a child process */
  pid = fork();
  printf("1\n");
  
  if (pid < 0) { /* error occured */
    fprintf(stderr, "Fork Failed");
    return 1;
  } else if (pid == 0) { /* child process */
    execlp("/bin/ls", "ls", NULL);
  } else {
    /* parent will wait for the child to complete */
    wait(NULL);
    printf("Child Complete\n");
  }

  return 0;
}

