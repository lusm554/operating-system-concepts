#include <stdio.h>
#include <unistd.h>
#include <errno.h> // errno
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 80 /* The max length of command */

/*
 * errno
 * 
 *  Value:   Description:
 *  0        No error
 *  EDOM     Domain error (from math)
 *  EILSEQ   Encoding error (from character conversion)
 *  ERANGE   Range error (from math)
 */

int main(void) {
  char line[MAX_LINE]; /* input line */
  char *args[MAX_LINE/2 + 1]; /* command line arguments */
  int should_run = 1; /* flag to determine when to exit program */
  

  while (should_run) {
    printf("osh>");
    fflush(stdout);
      
    fgets(line, sizeof(line), stdin);
    
    if (errno != 0) {
      perror("fgets");
    }

    if (strncmp(line, "exit", 4) == 0)
      break;
  }

  return 0;
}

