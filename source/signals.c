
#include "../../include/minishell.h"

void	check_signal(t_ms *s)
{
	// t_signal	signal;
	(void)s;

	if (signal(SIGINT, handle_signal))
		perror("can't catch SIGINT");
	else if (signal(SIGTERM, handle_signal))
		perror("can't catch SIGTERM");
	else if (signal(SIGQUIT, handle_signal))
		perror("can't catch SIGQUIT");
	else
		return ;
		// exit(0);
}

 /* argument is signal number */
void handle_signal(int sign)
{
	if (sign == SIGINT)	/* CTRL + C */
	{
		write(1, "^C\n", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sign == SIGTERM )	/* CTRL + D */ //&& s->modal == MAIN
		return (write(1, "exit\n", 5), exit(0));
	else if (sign == SIGTERM)	/* CTRL + D */ //&& s->modal == HEREDOC
		return (write(1, "\n", 1), exit(0));
	else if (sign == SIGQUIT)	 /* CTRL + \ */
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
