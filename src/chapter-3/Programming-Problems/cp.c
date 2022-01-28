#include <stdio.h>
#include <errno.h>

int main(int argc, void **argv) {
  if (argc != 3) return 1;

  FILE *fp_read;
  FILE *fp_write;
  int c;
  
  char *src = argv[1];
  char *dest = argv[2];

  fp_read = fopen(src, "r");
  fp_write = fopen(dest, "w");

  if (!fp_read || !fp_write) {
    perror("fopen");
    return 1;
  }

  while ((c = getc(fp_read)) != EOF)
    fputc(c, fp_write);

  fclose(fp_read);
  fclose(fp_write);

  return 0; 
}

