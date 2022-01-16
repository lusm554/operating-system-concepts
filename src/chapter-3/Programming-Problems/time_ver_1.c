#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define SIZE sizeof(long long int) * 2 // two nums
#define NAME "/time_counter"

int elapsed(struct timeval *start, struct timeval *end);
char *to_str_view(int all_msecs);

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "usage: ./time [command_to_execute]\n");
    return 1;
  }
  
  /* CREATE CHILD PROCESS */
  pid_t pid;
  pid = fork();

  if (pid < 0) { // error
    perror("fork()");
    return EXIT_FAILURE;
  }

  if (pid == 0) { // child
    /* TIMEVAL */
    struct timeval start;
    gettimeofday(&start, NULL);

    /* SHARED MEMORY */
    int fd = shm_open(NAME, O_CREAT | O_EXCL | O_RDWR, 0666);
    if (fd < 0) {
      perror("shm_open()");
      return EXIT_FAILURE;
    }

    if (ftruncate(fd, SIZE) < 0) {
      perror("ftruncate()");
      return EXIT_FAILURE; 
    }

    int *ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    //printf("sender mapped address: %p\n", ptr);

    ptr[0] = start.tv_sec;
    ptr[1] = start.tv_usec;    

    munmap(ptr, SIZE);
    close(fd);

    //execlp("/bin/ls", "ls", NULL);
    system(argv[1]);
  }

  if (pid > 0) { // parent
    wait(NULL);
    //printf("child complete\n");

    int fd = shm_open(NAME, O_RDONLY, 0666);
    if (fd < 0) {
      perror("shm_open() recv");
      return EXIT_FAILURE;
    }
    
    int *ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);
    //printf("receiver mapped address: %p\n", ptr);

    struct timeval start, end;

    start.tv_sec = ptr[0];
    start.tv_usec = ptr[1];

    printf("%d, %d\n", start.tv_sec, start.tv_usec);

    printf("\n\n\n%s", to_str_view(elapsed(&start, &end)));

    munmap(ptr, SIZE);
    close(fd);
    shm_unlink(NAME);
  }

  return 0;
}

// creates view of microseconds to seconds
char *to_str_view(int all_msecs) {
  int sec = all_msecs/1e+6;
  int msec = all_msecs%(int)1e+6;

  char *str;
  sprintf(str, "Elapsed time: %u.%u\n", sec, msec);

  return str;
}

// count diff between two timeval
int elapsed(struct timeval *start, struct timeval *end) {
  return ((end->tv_sec - start->tv_sec) * 1000000) + (end->tv_usec - start->tv_usec);
}

