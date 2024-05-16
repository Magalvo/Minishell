
#include "../include/minishell.h"

void	exit_minishell(t_ms *s)
{
	(void)s;
	exit(0);
}



int	init_minishell(t_ms *s, char **ep)
{
	(void)ep;

	s->prompt = "write here ->";	// v zero
	// s->prompt = "nanoshell ->";	// v alpha
	// s->prompt = "microshell";	// v beta
	// s->prompt = "minishell";	// v gold

	return (true);
}

void	handle_signal()
{
	// t_signal	signal;

	if (signal(SIGINT, sig_usr))
		perror("can't catch SIGINT");
	else if (signal(SIGTERM, sig_usr))
		perror("can't catch SIGTERM");
	else if (signal(SIGQUIT, sig_usr))
		perror("can't catch SIGQUIT");
	else
		return ;
		// exit(0);
}

 /* argument is signal number */
static void sig_usr(int signo)
{
	if (signo == SIGINT)
		printf("received SIGINT\n");
	else if (signo == SIGTERM)
		printf("received SIGTERM\n");
	else if (signo == SIGQUIT)
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
		handle_signal();
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
