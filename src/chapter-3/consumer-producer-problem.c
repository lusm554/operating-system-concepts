#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

void write_shm(void);
void read_shm(void);

int main(void) {
  write_shm();
  read_shm();

  return 0;
}

void write_shm(void) {
  /* the size (in bytes) of shared memory object */
  const int SIZE = 4096;
  /* name of the shared memory object */
  const char *name = "OS";
  
  /* strings written to shared memory */
  const char *msg_0 = "Hello";
  const char *msg_1 = "World!";

  /* shared memory file descriptor */
  int fd;
  /* pointer to shared memory object */
  char *ptr;


  /* create the shared memory object */
  fd = shm_open(name, O_CREAT | O_RDWR, 0666);

  printf("fd write - %u\n", fd);
  
  /* configure the size of the shared memory object */
  ftruncate(fd, SIZE);

  /* memory map the shared memory object */
  ptr = (char *)
    mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  /* write to the shared memory object */
  sprintf(ptr, "%s", msg_0);
  ptr += strlen(msg_0);
  sprintf(ptr, "%s", msg_1);
  ptr += strlen(msg_1);

}

void read_shm(void) {
  /* the size (in bytes) of shared memory object */ 
  const int SIZE = 4096;
  /* name of the shared memory object */
  const char *name = "OS";
  /* shared memory file descriptor */
  int fd;
  /* pointer to shared memory object */
  char *ptr;


  /* open the shared memory object */
  fd = shm_open(name, O_RDONLY, 0666);

  printf("fd read - %u\n", fd);

  /* memory map the shared memory object */
  ptr = (char *)
    (mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
  
  /* read from the shared memory object */
  printf("%s", (char*)ptr);

  /* remove the shared memory object */
  shm_unlink(name);

}


