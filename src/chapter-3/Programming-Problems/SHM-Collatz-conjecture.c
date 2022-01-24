#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define NAME "/Collatz_conjecture"
#define MAX_SEQ_SIZE 500
#define SIZE sizeof(int) * MAX_SEQ_SIZE

long to_num(char *str);

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "usage: ./a.out [num]\n");
    return 1;
  }

  long num;
  if ((num = to_num(argv[1])) == -1) {
    perror("incorrect integer");
    return 1;
  }

  /* SHM */
  int fd = shm_open(NAME, O_CREAT | O_EXCL | O_RDWR, 0666);
  if (fd < 0) {
    perror("sh_open()");
    return EXIT_FAILURE;
  }

  if (ftruncate(fd, SIZE) < 0) {
    perror("ftruncate()");
    return EXIT_FAILURE;
  }

  int *ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  /* CHILD PROCESS */
  pid_t pid;
  pid = fork();

  if (pid < 0) { //error
    perror("fork()");
    return EXIT_FAILURE;
  }

  if (pid == 0) { // child
    int i = 0;
    while (num != 1) {
      ptr[i] = num;

      if (num % 2 == 0)
        num /= 2;
      else
        num = 3 * num + 1;
    
      if (i == MAX_SEQ_SIZE)
        return 1;

      i++;
    }

    ptr[i] = 1;
    ptr[++i] = -1;
  }

  if (pid > 0) { // parent
    wait(NULL);
    
    int i = 0;
    while (ptr[i] != -1) {
      printf("%d ", ptr[i++]);
    } 
    printf("\n");

    // remove shm
    munmap(ptr, SIZE);
    close(fd);
    shm_unlink(NAME);
  }


	return 0;
}

long to_num(char *str) {
  char *p;

  errno = 0;
  long num = strtol(str, &p, 10);

  if (errno != 0 || *p != '\0' || num > INT_MAX || num < 0) {
    return -1;
  }
    
  return num;
}

