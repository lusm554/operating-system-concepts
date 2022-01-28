#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


#define READ_END 0
#define WRITE_END 1

int main(int argc, void **argv) {
  if (argc != 3) return 1;

  char *src = argv[1];
  char *dest = argv[2];

  FILE *fp_read;
  FILE *fp_write;
  int fd[2];
  pid_t pid;
    
  /* Create the pipe */
  if (pipe(fd)) {
    perror("pipe");
    return EXIT_FAILURE;
  }
  
  pid = fork();

  /* parent */
  if (pid > 0 ) {
    if (!(fp_read = fopen(src, "r"))) {
      perror("fopen");
      return EXIT_FAILURE;
    }

    int c;
    FILE *stream;

    stream = fdopen(fd[WRITE_END], "w");
    close(fd[READ_END]);

    while ((c = getc(fp_read)) != EOF)
      fprintf(stream, "%c", c);

    fclose(stream);
    fclose(fp_read);
    close(fd[WRITE_END]);
    wait(NULL);
  }

  /* child */
  if (pid == 0) {
    FILE *stream;
    int c;

    if (!(fp_write = fopen(dest, "w"))) {
      perror("fopen");
      return EXIT_FAILURE;
    }   

    close(fd[WRITE_END]);
    stream = fdopen(fd[READ_END], "r");

    while ((c = fgetc(stream)) != EOF)
      fputc(c, fp_write);

    fclose(fp_write);
    fclose(stream);
    close(fd[READ_END]);
  }

  /* error */
  if (pid < 0) {
    perror("fork");
    return EXIT_FAILURE;
  }

  return 0; 
}


