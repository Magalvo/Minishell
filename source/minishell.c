// header goes here

#include "../include/minishell.h"
// #include <signal.h>
// #include <unistd.h>
// #include <stdio.h>
// #include <readline/readline.h>
// #include <readline/history.h>

t_minis g_minis;

void exit_minishell(t_minis *s, char *msg)
{
	if (msg)
		write(1, "exit\n", ft_strlen(msg));
	(void)s;
	exit(0);
}

int init_minishell(t_minis *s, char **ep)
{
	(void)ep;

	s->modal = MAIN;
	s->prompt = "minishell>";    // v zero
	// s->prompt = "nanoshell ->";  // v alpha
	// s->prompt = "microshell";    // v beta
	// s->prompt = "minishell";     // v gold

	return (true);
}


// STATUS: signal caught, ctrl+\ shouldn't prints to stdout
void minishell(char **envp)
{
	t_minis s;
	char *input;

	if (!init_minishell(&s, envp))
		exit_minishell(&s, NULL);
	while (true)
	{
		check_signal(&s);
		input = readline(s.prompt);
		if (input == NULL && s.modal == MAIN)
			exit_minishell(&s, "exit\n");
		// todo
		/* lexer
        ft_tokenizer;
		parser
		expander
		executor */
		/* if (cmd_exec(input) == 0)
			break; */
		ft_dprintf(STDOUT_FILENO, "%s\n", input);
		free(input);
	}
	exit_minishell(&s, NULL);
}

int main(int argc, char *argv[], char *envp[])
{
	(void)argv;

	if (argc != 1)
		return (0);
	minishell(envp);
	return (0);
}
