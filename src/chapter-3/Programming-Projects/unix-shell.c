#include <stdio.h>
#include <unistd.h>
#include <errno.h> // errno
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 80 /* The max length of command */

char **split(char line[MAX_LINE], char *list[MAX_LINE]);

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

    fgets(line, sizeof(line), stdin); /* get line from stdin */
    if (errno != 0) {
      perror("fgets");
    }

    if (strncmp(line, "exit", 4) == 0) /* check first four chars on 'exit' */
      break;

    split(line, args); /* parse tokens */
    
    /*
    int i = 0;
    do 
      printf("w: %s\n", args[i]);
    while (args[i++] != '\0');
    */
    printf("w1: %sn", args[1]);
  }

  return 0;
}

char **split(char line[MAX_LINE], char *list[MAX_LINE]) {
  char *token;
  int i = 0;

  if ((token = strtok(line, " ")) != NULL) {
    do {
      list[i++] = token;
    } while ((token = strtok(NULL, " ")) != NULL);
    list[i] = '\0';
    return list;
  }   
  
  exit(1);
}

