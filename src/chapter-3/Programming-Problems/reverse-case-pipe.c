#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE 25
#define READ_END 0
#define WRITE_END 1

void read_pipe(int *fd, char *read_msg);
void write_pipe(int *fd, char *write_msg);

int main(void) {
  // parent buf 
  char write_msg_p[SIZE] = "hello";
  char read_msg_p[SIZE];
  // child buf
  char write_msg_c[SIZE] = "not hello";
  char read_msg_c[SIZE];

  int fd_p[2]; // parent pipe
  int fd_c[2]; // child pipe

  pid_t pid;

  /* create the pipe */
  if ((pipe(fd_p) == -1) || (pipe(fd_c) == -1)) {
    perror("pipe");
    return 1;
  }

  pid = fork(); // fork child process

  if (pid < 0) { // error
    perror("fork");
    return 1;
  }

  if (pid > 0) { // parent 1
    write_pipe(fd_p, write_msg_p);

    wait(NULL);

    read_pipe(fd_c, read_msg_c);
    printf("parent: read '%s'\n", read_msg_c);

  }

  if (pid == 0 ) { // child 2
    read_pipe(fd_p, read_msg_p);
    printf("child: read '%s'\n", read_msg_p);

    write_pipe(fd_c, write_msg_c);
  }

  return 0;
}

void write_pipe(int *fd, char *write_msg) {
  close(fd[READ_END]);
  write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);
  close(fd[WRITE_END]);
}

void read_pipe(int *fd, char *read_msg) {
  close(fd[WRITE_END]);
  read(fd[READ_END], read_msg, SIZE);
  close(fd[READ_END]);
}

