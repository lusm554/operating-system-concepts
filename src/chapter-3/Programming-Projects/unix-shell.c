#include <stdio.h>
#include <unistd.h>
#include <errno.h> // errno
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_LINE  256 /* The max length of command */
#define MAX_TOKEN 64
#define TOK_DELIM " \t\r\n\a"

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
char **split_line(char *line);
int execute(char **args);
int launch(char **args, int isBackground);

int main(void) {
  char *line;
  char **args;
  int should_run = 1;
  
  while (should_run) {
    printf("osh>");

    // Calls force the output to standard output.
    fflush(stdout);
    line = read_line();
    args = split_line(line);
    
    // Check first four chars on 'exit'.
    if (strncmp(line, "exit", 4) == 0) {
      free(line);
      free(args);
      break;
    }

    should_run = execute(args);

    free(line);
    free(args);
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

char **split_line(char *line) {
  char **tokens = malloc(MAX_TOKEN * sizeof(char *));
  char *token;
  int i = 0;

  if (!tokens) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, TOK_DELIM);
  while (token != NULL) {
    tokens[i] = token;
    i++;

    if (i >= MAX_TOKEN * sizeof(char *)) {
      perror("too big token");
      exit(EXIT_FAILURE);
    }

    token = strtok(NULL, TOK_DELIM);
  }

  tokens[i] = NULL;
  return tokens;
}

int execute(char **args) {
  // An empty command was entered.
  if (args[0] == NULL) {
    return 1;
  }

  int isBackground;
  int i = 0;
  while (args[i] != NULL) {
    if (strncmp(args[i++], "&", 1) == 0 && args[i+1] == NULL) {
      isBackground = 1; 
    }
  }

  return launch(args, isBackground);
}

int launch(char **args, int isBackground) {
  pid_t pid, wpid;
  int status;
  
  pid = fork();

  // Child process.
  if (pid == 0) {
    printf("\n");
    if (execvp(args[0], args) == -1) {
      perror("execvp");
    }
    exit(EXIT_FAILURE);
  }

  // Parent process.
  if (pid > 0) {
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  // Error forking.
  if (pid < 0) {
    perror("fork");
  }

  return 1;
}

