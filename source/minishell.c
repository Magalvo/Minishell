#include "../include/minishell.h"
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void exit_minishell(t_ms *s)
{
	(void)s;
	exit(0);
}

int init_minishell(t_ms *s, char **ep)
{
	(void)ep;

	s->modal = MAIN;
	s->prompt = "write here ->";    // v zero
	// s->prompt = "nanoshell ->";  // v alpha
	// s->prompt = "microshell";    // v beta
	// s->prompt = "minishell";     // v gold

	return (true);
}

void minishell(char **envp)
{
	t_ms s;
	char *input;

	if (!init_minishell(&s, envp))
		exit_minishell(&s);
	while (true)
	{
		check_signal(&s);
		input = readline(s.prompt);
		if (input == NULL)
			break;  // Handle EOF (Ctrl+D)
		// lexer
		// parser
		// expander
		// executor
		ft_dprintf(STDOUT_FILENO, "%s\n", input);
		free(input);
	}
	exit_minishell(&s);
}

int main(int argc, char *argv[], char *envp[])
{
	(void)argv;

	if (argc != 1)
		return (0);
	minishell(envp);

	return (0);
}
