// header goes here

#include "../include/minishell.h"

// check siginfo_DontUse
void handler(int signo, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;

	if (signo == SIGINT) /* CTRL + C */
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_ignore(struct sigaction *sa, int signal)
{
	struct	sigaction	sa_origin;
	int					sa_origin_flags;

	sa_origin_flags = sa->sa_flags;
	sa->sa_handler = SIG_IGN;
	sa->sa_flags |= SA_SIGINFO;
	if (sigemptyset(&sa->sa_mask) != 0)
		return ;
	sigaction(signal, sa, &sa_origin);
	sa->sa_flags = sa_origin_flags;
}

void	here_handler(int signal, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signal == SIGINT)
		exit(130);
}

void	check_signal(e_signal sig)
{
	static struct sigaction sa;

	if (sig == MAIN)
	{
		sa.sa_sigaction = handler;
		sa.sa_flags = SA_SIGINFO;
		if (sigemptyset(&sa.sa_mask) != 0)
			return ;
		sigaction (SIGINT, &sa, NULL);
		sig_ignore(&sa, SIGQUIT);
	}
	else if (sig == CHILD)
	{
		sa.sa_handler = SIG_DFL;
		sa.sa_flags = 0;
		if (sigemptyset(&sa.sa_mask) != 0)
			return ;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
	else if (sig == HERE_DOC)
	{
		sa.sa_sigaction = here_handler;
		sa.sa_flags = SA_SIGINFO;
		if (sigemptyset(&sa.sa_mask) != 0)
			return ;
		sigaction(SIGINT, &sa, NULL);
		sig_ignore(&sa, SIGQUIT);
	}
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

/*
void check_signal(t_minis *s)
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
 */

// advanced programming...enviromment: 10.14
/* void check_signal(t_ms *s)
{
	(void)s;

	struct sigaction sa;

	// sa.sa_handler = handle_signal;
	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	// sa.sa_flags = 0;

	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	else if (sigaction(SIGINT, &sa, NULL) == -1)
		perror("can't catch SIGINT");
	else if (sigaction(SIGTERM, &sa, NULL) == -1)
		perror("can't catch SIGTERM");

} */
