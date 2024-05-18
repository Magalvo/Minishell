
#include "../include/minishell.h"

void check_signal(t_ms *s)
{
	(void)s;

	struct sigaction sa;
	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	if (sigaction(SIGINT, &sa, NULL) == -1)
		perror("can't catch SIGINT");
	else if (sigaction(SIGTERM, &sa, NULL) == -1)
		perror("can't catch SIGTERM");
	else if (sigaction(SIGQUIT, &sa, NULL) == -1)
		perror("can't catch SIGQUIT");
}

/* argument is signal number */
void handle_signal(int sign)
{
	if (sign == SIGINT) /* CTRL + C */
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sign == SIGTERM) /* CTRL + D */
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	else if (sign == SIGQUIT) /* CTRL + \ */
		write(1, "SIGQUIT\n", 8);
	else
		exit(0);

}


//use write() and not printf() for handling SIGNALS // MIGHT CRASH

// int	handle_signal(int num)
// {
// 	write (1, "\n", 1);
// 	write (1, "Exit", 4);
// 	exit(1);
// }
