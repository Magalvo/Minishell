
#include "../include/minishell.h"

void	exit_minishell(t_ms *s)
{
	(void)s;
	exit(0);
}



int	init_minishell(t_ms *s, int ac, char **av, char **ep)
{
	(void)ac;
	(void)av;
	(void)ep;

	s->prompt = "write here ->";	// v zero
	// s->prompt = "nanoshell ->";	// v alpha
	// s->prompt = "microshell";	// v beta
	// s->prompt = "minishell";	// v gold

	return (true);
}
// lexer -> parser -> expander -> executor
int main(int argc, char *argv[], char *envp[])
{
	t_ms	s;
	char	*input;

	if (!init_minishell(&s, argc, argv, envp))
		exit_minishell(&s);
	while (true)
	{
		// lexer
		// parser
		// expander
		// executor
		input = readline(s.prompt);
		ft_dprintf(STDOUT_FILENO, "%s\n", input);
	}
	return (0);
}
