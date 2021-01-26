#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sd_arch_bf(char *str, size_t m, char *search, size_t n) {
  int i=0, j=0;
  while (i<m && j<n) {
    if (str[i]==search[j]) {
      i++;
      j++;
    } else {
      i=i-j+1; //从上次匹配的下一个开始
      j=0;
    }
  }
  if (j==n) {
    return i-n;
  }
  return -1;
}

void sd_arch_test_bf(char *str, char *search) {
  size_t m = strlen(str);
  size_t n = strlen(search);
  int index = sd_arch_bf(str, m, search, n);
  printf("sd_arch_test_bf(\"%s\", %zu, \"%s\", %zu) == %d\n", str, m, search, n, index);
}

int main() {
  sd_arch_test_bf("hello world!", "wor");
  sd_arch_test_bf("hello world!", "hell");
  sd_arch_test_bf("hello world!", "abc");
  return 0;
}
