#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE 25
#define READ_END 0
#define WRITE_END 1


void write(fd, &read_msg);
void read(fd, &write_msg);

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
    close(fd_p[READ_END]);

    write(fd_p[WRITE_END], write_msg_p, strlen(write_msg_p) + 1);

    close(fd_p[WRITE_END]);

    wait(NULL);

    close(fd_c[WRITE_END]);
    
    read(fd_c[READ_END], read_msg_c, SIZE);
    printf("parent: read '%s'\n", read_msg_c);

    close(fd_c[READ_END]); 

  }

  if (pid == 0 ) { // child 2
    close(fd_p[WRITE_END]);
    
    read(fd_p[READ_END], read_msg_p, SIZE);
    printf("child: read '%s'\n", read_msg_p);

    close(fd_p[READ_END]);

    close(fd_c[READ_END]);

    write(fd_c[WRITE_END], write_msg_c, strlen(write_msg_c) + 1);

    close(fd_c[WRITE_END]);
  }

  return 0;
}

void write(fd, &read_msg) {
   
}

void read(fd, &write_msg) {

}

