#include <stdio.h>
#include <errno.h>
#include <limits.h>

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
  printf("%llu\n", ULLONG_MAX);

  //errno = ERANGE;
  if (errno != 0) {
    perror("math, math, math...");
  }
  
  return 0;
}

