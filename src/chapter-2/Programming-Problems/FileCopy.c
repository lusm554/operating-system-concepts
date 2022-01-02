#include <stdio.h>
#include <unistd.h>

/*
Write cp program using either the POSIX or Windows API.
Be sure to include all necessary error checking, including ensuring that the source file exists.
Input:
  1. source file
  2. destination file
*/

#define ENOENT 64 // machine is not on the network (args < 2)
#define EPERM   1 // operation not permitted (source not exist)

int main(int argc, char *argv[]) {
  // check amount of args
  if (argc != 3) return ENOENT;
  
  char *src = argv[1];  
  char *dest = argv[2];  
  
  // check file existence 
  if (access(src, F_OK) != 0) return EPERM;

  // Read
  FILE *inputp;
  int inputcc;
  inputp = fopen(src, "r");

  // Write
  FILE *outputp;
  outputp = fopen(dest, "w");

  // Copy data
  while ((inputcc = fgetc(inputp)) != EOF)
    fputc(inputcc, outputp);

  fclose(inputp);
  fclose(outputp);
  return 0;
}

