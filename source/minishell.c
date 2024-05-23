// header goes here

#include "../include/minishell.h"
// #include <signal.h>
// #include <unistd.h>
// #include <stdio.h>
// #include <readline/readline.h>
// #include <readline/history.h>

void exit_minishell(t_ms *s, char *msg)
{
	if (msg)
		ft_putstr_fd(msg, 1);
	(void)s;
	ft_free_dptr(s->paths);
	ft_free_dptr(s->cmd_temp);
	exit(0);
}

int init_minishell(t_ms *s, char **ep)
{
	init_env(s, ep);
	init_paths(s, ep);
	//todo this as it should be
	s->modal = MAIN;
	s->prompt = "write_here ->";    // v zero
	// s->prompt = "nanoshell ->";  // v alpha
	// s->prompt = "microshell";    // v beta
	// s->prompt = "minishell";     // v gold

	return (true);
}


// STATUS: signal caught, ctrl+\ shouldn't print to stdout
void minishell(char **envp)
{
	t_ms	s;
	char	*input;
	//int		i;

	if (!init_minishell(&s, envp))
		exit_minishell(&s, NULL);
	t_env *current = s.env;
    while (current) 
	{
    	printf("%s=%s\n", current->key, current->value);
    	current = current->next;
    }
	while (true)
	{
		//i = 0;
		check_signal(&s);
		input = readline(s.prompt);
		if (input == NULL && s.modal == MAIN)
			exit_minishell(&s, "exit\n");
		split_input(&s, input);
		/* while (s.paths[i])
		{
			ft_putendl_fd(s.env[i], 1);
			i++;
		} */
		exec_input(&s); // ! make this
		// todo
		/* lexer
        ft_tokenizer;
		parser
		expander
		executor */
		/* if (cmd_exec(input) == 0)
			break; */
		//ft_dprintf(STDOUT_FILENO, "%s\n", input);
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
