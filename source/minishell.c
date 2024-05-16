
#include "../include/minishell.h"

void	exit_minishell(t_ms *s)
{
	(void)s;
	exit(0);
}



int	init_minishell(t_ms *s, char **ep)
{
	(void)ep;

	s->modal = MAIN;
	s->prompt = "write here ->";	// v zero
	// s->prompt = "nanoshell ->";	// v alpha
	// s->prompt = "microshell";	// v beta
	// s->prompt = "minishell";	// v gold

	return (true);
}

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
static void handle_signal(int sign, t_ms *s)
{
	if (sign == SIGINT)	/* CTRL + C */
		printf("received SIGINT\n");
	else if (sign == SIGTERM && s->modal == MAIN)	/* CTRL + D */
		return (printf("exit\n"), exit(0));
	else if (sign == SIGQUIT)	 /* CTRL + \ */
		printf("received SIGQUIT\n");
	else
		exit(0);
}

void	minishell(char **envp)
{
	t_ms	s;
	char	*input;

	(void)envp;

	if (!init_minishell(&s, envp))
		exit_minishell(&s);
	while (true)
	{
		check_signal(&s);
		input = readline(s.prompt);
		// lexer
		// parser
		// expander
		// executor
		ft_dprintf(STDOUT_FILENO, "%s\n", input);
	}

}

// lexer -> parser -> expander -> executor
int main(int argc, char *argv[], char *envp[])
{

	(void)argv;

	if (argc != 1)
		return (0);
	minishell(envp);

	return (0);
}
