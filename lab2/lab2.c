#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  char *buff = NULL;
  size_t size = 0;

  while (1) {
    printf("Enter programs to run.\n> ");

    ssize_t n = getline(&buff, &size, stdin);
    if (n == -1) {
      break;
    }

    if (n > 0 && buff[n - 1] == '\n') {
      buff[n - 1] = '\0';
    }

    pid_t pid = fork();
    if (pid == -1) {
      perror("fork");
      free(buff);
      exit(EXIT_FAILURE);
    }

    if (pid == 0) {
      execlp(buff, buff, (char *)NULL);
      printf("Exec failure\n");
      free(buff);         // child owns a copy of the buffer too
      exit(EXIT_FAILURE); // MUST exit, or the child re-enters the loop
    } else {
      if (waitpid(pid, NULL, 0) == -1) {
        perror("waitpid");
        free(buff);
        exit(EXIT_FAILURE);
      }
    }
  }

  free(buff);
  return 0;
}
