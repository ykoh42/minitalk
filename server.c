#include <limits.h>
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

static void ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
  {
		write(fd, "-", 1);
  }
	if (n == INT_MIN)
  {
		write(fd, "2147483648", 10);
    return ;
  }
	n = (n < 0) ? -n : n;
	if (n > 9)
  {
		ft_putnbr_fd(n / 10, fd);
  }
	write(fd, &"0123456789"[n % 10], 1);
}


int     main(void) {
  pid_t pid = getpid();
  ft_putnbr_fd(pid, 1);
  write(1,"\n", 1);
  signal(SIGUSR1, sig_handler);
  signal(SIGUSR2, sig_handler);
  while (1) {
    pause();
  }

  return (0);
}