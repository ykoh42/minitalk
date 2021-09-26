#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <strings.h>

static void sig_handler(int sig) {
  //// 11111100 00011110 00100101 00000000
  static char buf[100000000] = {'\0', };
  static int bit = 7;
  static int i = 0;

  if (sig == SIGUSR1) {
    buf[i] |= (1 << bit);
    //printf("1 %d\n", bit);
  }
  if (sig == SIGUSR2) {
    buf[i] &= ~(1 << bit);
    //printf("0 %d\n", bit);
  }
  bit--;

  if (bit == -1) {
    bit = 7;
    if (buf[i] == '\0') {
      write(1, buf, i);
      i = 0;
    } else {
      i++;
    } 
  }

}

int     main(void) {
  pid_t pid = getpid();
  printf("%d\n", pid);
  signal(SIGUSR1, sig_handler);
  signal(SIGUSR2, sig_handler);
  while (1) {
    pause();
  }

  return (0);
}