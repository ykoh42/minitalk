#include <limits.h>
#include <unistd.h>
#include <signal.h>

static void send_char(pid_t pid, char c) {
  int bit = 7;

  while (bit != -1) {
    if (c & (1 << bit)) {
      kill(pid, SIGUSR1);
    } else {
      kill(pid, SIGUSR2);
    }
    bit--;
    usleep(100);
  }
}

static void send_str(pid_t pid, char *str) {
  int i = 0;
  while (str[i]) {
    send_char(pid, str[i]);
    i++;
  }
  send_char(pid, '\0');
}

static int  ft_atoi(const char *str)
{
	char				neg;
	unsigned long long	num;

	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	neg = (*str == '-');
	if (*str == '+' || *str == '-')
		str++;
	num = 0;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	if (num > LONG_MAX - 1 && neg == 1)
		return (0);
	if (num > LONG_MAX && neg == 0)
		return (-1);
	return (neg ? -num : num);
}

int         main(int argc, char*argv[]) {
  if (argc < 3) {
    return (1);
  }
  pid_t pid = ft_atoi(argv[1]);
  char  *str = argv[2];

  send_str(pid, str);

  return (0);
}