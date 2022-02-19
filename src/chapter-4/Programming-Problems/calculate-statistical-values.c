#include <stdio.h>

int avg(int *arr, int len);
int max(int *arr, int len);
int min(int *arr, int len);

int main() {
  int test[] = {1, 2, 3, 4, 5};

  int av = avg(test, (int)(sizeof(test)/sizeof(int)));
  int mi = min(test, (int)(sizeof(test)/sizeof(int))); 
  int ma = max(test, (int)(sizeof(test)/sizeof(int)));

  printf("avg: %d, max: %d, min: %d\n", av, ma, mi);
  return 0;
}


int avg(int *arr, int len) {
  int sum = 0;

  for (int i = 0; i < len; i++) {
    sum += arr[i];
  }
  
  return sum/len;
}

int max(int *arr, int len) {
  int m = arr[0];
  
  for (int i = 0; i < len; i++) {
    if (arr[i] > m) {
      m = arr[i];
    }
  }

  return m;
}
    
int min(int *arr, int len) {
   int m = arr[0];
  
  for (int i = 0; i < len; i++) {
    if (arr[i] < m) {
      m = arr[i];
    }
  }

  return m; 
}
