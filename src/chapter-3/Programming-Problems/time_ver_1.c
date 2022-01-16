#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define SIZE sizeof(long long int) 
#define NAME "/time_counter"

int elapsed(struct timeval *start, struct timeval *end);
char *to_str_view(int all_msecs);

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "usage: ./time [command_to_execute]\n");
    return 1;
  }
  
  /* ELAPSED TIME */
  struct timeval start, end;                                                                        

  gettimeofday(&start, NULL);                                                                       

  sleep(3);                                                                                         
  gettimeofday(&end, NULL);                                                                       

  int el = elapsed(&start, &end);  

  char *view = to_str_view(el);
  printf("%s", view);
  
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

  printf("sender mapped address: %p\n", ptr);

  // write to the shm object
  ptr[0] = el;
  
  munmap(ptr, SIZE);
  close(fd);

  /* TEST RECEIVING DATE FROM SHM */
  {
    int fd = shm_open(NAME, O_RDONLY, 0666);
    if (fd < 0) {
      perror("shm_open() recv");
      return EXIT_FAILURE;
    }
    
    int *ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);
    printf("receiver mapped address: %p\n", ptr);

    printf("data: %d\n", ptr[0]);

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

