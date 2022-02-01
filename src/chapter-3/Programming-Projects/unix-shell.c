#include <stdio.h>
#include <unistd.h>
#include <errno.h> // errno
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 256 /* The max length of command */

/*
 * errno
 * 
 *  Value:   Description:
 *  0        No error
 *  EDOM     Domain error (from math)
 *  EILSEQ   Encoding error (from character conversion)
 *  ERANGE   Range error (from math)
 */

char *read_line(void);

int main(void) {
  char *line;
  char **args;
  int should_run = 1;
  
  while (should_run) {
    printf("osh>");
    fflush(stdout);
    line = read_line();
    
    /*
    fgets(&line, sizeof(line), stdin); // get line from stdin
    if (errno != 0) {
      perror("fgets");
    }

    */
    if (strncmp(line, "exit", 4) == 0) {// check first four chars on 'exit' 
      free(line);
      break;
    }
    free(line);
  }

  return 0;
}

char *read_line(void) {
  char *line = malloc(sizeof(char) * MAX_LINE);
  int i = 0;
  int c;
  
  if (!line) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  while (1) {
    // Read char from stdin.
    c = getchar();
    printf("c: %c\n", c);

    // If get EOF, replace it will null char and return.
    if (c == EOF || c == '\n') {
      line[i] = '\0';
      return line;
    } else {
      line[i] = c;
    }
    i++;

    // If input exceeded the line buffer, error.
    if (i >= MAX_LINE) {
      perror("too big line");
      exit(EXIT_FAILURE);
    }
  }
}
