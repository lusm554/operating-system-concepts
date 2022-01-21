#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <wait.h>

long to_num(char *str);

int main(int argc, char **argv) {
  if (argc != 2) return 1;
    
  long num;
  if ((num = to_num(argv[1])) == -1) return 1;

  printf("Input: %s\n", argv[1]);
 
  pid_t pid;
  pid = fork(); 

  if (pid < 0) // error
    return 1;

  if (pid == 0) { // child
    while (num != 1) {
      printf("%ld ", num);
      if (num % 2 == 0) {
        num /= 2;
      } else {
        num = 3 * num + 1;
      }
    }
    printf("1\n");
  }
  
  if (pid > 0) { // parent
    wait(NULL);
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

