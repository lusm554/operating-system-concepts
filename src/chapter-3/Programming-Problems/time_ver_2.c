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

int elapsed(struct timeval *start, struct timeval *end);
char *to_str_view(int all_msecs);

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "usage: ./time [command_to_execute]\n");
    return 1;
  }

  int write_msg[SIZE];
  int read_msg[SIZE];

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
    struct timeval start;
    gettimeofday(&start, NULL);

    write_msg[0] = start.tv_sec;
    write_msg[1] = start.tv_usec;

    system(argv[1]);
        
    close(fd[READ_END]);
    write(fd[WRITE_END], write_msg, SIZE);
    close(fd[WRITE_END]);
  }

  if (pid > 0) { // parent
    close(fd[WRITE_END]);

    // read pointer
    read(fd[READ_END], read_msg, SIZE);

    struct timeval start, end;
    gettimeofday(&end, NULL);

    start.tv_sec = read_msg[0];
    start.tv_usec = read_msg[1];

    close(fd[READ_END]);
  
    printf("%s", to_str_view(elapsed(&start, &end)));

    wait(NULL);
  }

  return 0;
} 

// creates view of microseconds to seconds
char *to_str_view(int all_msecs) {
  int sec = all_msecs/1e+6;
  int msec = all_msecs%(int)1e+6;

  char *str;
  sprintf(str, "\nElapsed time: %u.%u\n", sec, msec);

  return str;
}

// count diff between two timeval
int elapsed(struct timeval *start, struct timeval *end) {
  return ((end->tv_sec - start->tv_sec) * 1000000) + (end->tv_usec - start->tv_usec);
}

