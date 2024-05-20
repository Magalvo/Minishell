// header goes here

#include "../include/minishell.h"

/*
void check_signal(t_ms *s)
{
	(void)type;

	static struct sigaction sa;
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
	(void)info;
	(void)context;
	// ucontext_t *context = (ucontext_t *)ptr;

	// if (info->si_signo == SIGTERM) /* CTRL + D */
	// {
	// 	write(1, "exit\n", 5);
	// 	exit(0);
	// }
	if (signo == SIGINT) /* CTRL + C */
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	// ! still printing to stdout
	else if (signo == SIGQUIT) /* CTRL + \ */
	{
		rl_replace_line("", 0);
		rl_redisplay();
		// return ;
		// write(1, "SIGQUIT\n", 8);
	}
	// printf("Received signal %d\n", signo);
	// printf("Signal originates from process %lu\n", (unsigned long)info->si_pid);
}

/* argument is signal number */
// void handle_signal(int sign)
// {
// 	if (sign == SIGINT) /* CTRL + C */
// 	{
// 		write(1, "\n", 1);
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// 	// ? handled at readline, not needed
// 	else if (sign == SIGTERM) /* CTRL + D */
// 	{
// 		write(1, "exit\n", 5);
// 		exit(0);
// 	}
// 	else if (sign == SIGQUIT) /* CTRL + \ */
// 	{
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 		// return ;
// 		// write(1, "SIGQUIT\n", 8);
// 	}
// 	else
// 		exit(0);
// }
