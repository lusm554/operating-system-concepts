#include <stdio.h>
#include <omp.h>

int main(void) {
  #pragma omp parallel
  {
    printf("I'm a parallel region.\n");
  }

  return 0;
}

