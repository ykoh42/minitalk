#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static void send_char(pid_t pid, char c) {
  //printf("%c: ", c);
  int bit = 7;

  while (bit != -1) {
    if (c & (1 << bit)) {
      kill(pid, SIGUSR1);
      //printf("1");
    } else {
      kill(pid, SIGUSR2);
      //printf("0");
    }
    bit--;
    usleep(100);
  }
  //printf("\n");
}

static void send_str(pid_t pid, char *str) {
  int i = 0;
  while (str[i]) {
    send_char(pid, str[i]);
    i++;
  }
  send_char(pid, '\0');
}

int         main(int argc, char*argv[]) {
  if (argc < 3) {
    return (1);
  }
  pid_t pid = atoi(argv[1]);
  char  *str = argv[2];

  send_str(pid, str);

  return (0);
}