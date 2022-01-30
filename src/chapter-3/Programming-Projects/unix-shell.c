#include <stdio.h>
#include <errno.h>

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

  errno = ERANGE;
  
  if (errno != 0) {
    perror("math, math, math...");
  }
  
  return 0;
}

