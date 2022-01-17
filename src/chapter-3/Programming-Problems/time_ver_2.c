#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>

#define SIZE 128
#define READ_END 0
#define WRITE_END 1

int main(void) {
  struct timeval start;
  gettimeofday(&start, NULL);
  
  char write_msg[SIZE] = "hello";
  char read_msg[SIZE];

  int fd[2];
  pid_t pid;

  if (pipe(fd) == -1) {
    perror("pipe()");
    return EXIT_FAILURE;
  }
  
  pid = fork();

  if (pid < 0) { // error
    perror("fork()");
    return EXIT_FAILURE;
  }

  if (pid == 0) { // child 
    close(fd[WRITE_END]);
    read(fd[READ_END], read_msg, SIZE);
    printf("read: %s\n", read_msg);
    
    close(fd[READ_END]);
    
  }

  if (pid > 0) { // parent
    close(fd[READ_END]);
    write(fd[WRITE_END], write_msg, strlen(write_msg)+1);

    close(fd[WRITE_END]);

    wait(NULL);
  }

  return 0;
} 

