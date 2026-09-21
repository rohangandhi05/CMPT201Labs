#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char *buff = NULL;
  size_t size = 0;

  while (1) {
    printf("Please enter some text: ");

    ssize_t n = getline(&buff, &size, stdin);
    if (n == -1) {
      // -1 here means EOF (Ctrl-D): quit the loop.
      break;
    }

    // getline keeps the trailing '\n'; strip it so the last token is clean.
    if (n > 0 && buff[n - 1] == '\n') {
      buff[n - 1] = '\0';
    }

    printf("Tokens:\n");

    char *saveptr;
    char *tok = strtok_r(buff, " ", &saveptr); // 1st call: real string
    while (tok != NULL) {
      printf("  %s\n", tok);
      tok = strtok_r(NULL, " ", &saveptr); // 2nd+ calls: NULL
    }
  }

  free(buff);
  return 0;
}
