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
	if (s->paths != NULL)
		ft_free_dptr(&s->paths);
	if (s->cmd_temp != NULL)
		ft_free_dptr(&s->cmd_temp);
	exit(EXIT_SUCCESS);
}

int init_minishell(t_ms *s, char **ep)
{
	init_env(s, ep);
	init_export(s, ep);
	env_paths(s, ep);
	//todo this as it should be
	s->env_tmp = ep;				//! added raw env for execve
	s->modal = MAIN;
	s->cmd_temp = NULL;
	// s->prompt = "write_here ->";    // v zero
	s->prompt = "\e[3;33mnanoshell\e[0m\e[1;97m -> \e[0m";  // v alpha
	// s->prompt = "\e[3;33mnanoshell\e[0m\e[1;97m -> \e[0m";    // v beta
	// s->prompt = "\e[3;33mminishell\e[0m\e[1;97m -> \e[0m";     // v gold
	return (true);
}


// STATUS: signal caught, ctrl+\ shouldn't print to stdout
void minishell(char **envp)
{
	t_ms	s;
	char	*input;
	// int		not_builtin;
	// int i;

	if (!init_minishell(&s, envp))
		exit_minishell(&s, NULL);
	while (true)
	{
		check_signal(MAIN);
		input = readline(s.prompt);
		if (input == NULL && s.modal == MAIN)
			exit_minishell(&s, "exit\n");
		// ast_factory(&s, input); // ! make this
		split_input(&s, input); // not needed
		// i = 0;
		/* while (s.paths[i])
		{
			ft_putendl_fd(s.paths[i], 1);
			i++;
		} */
		s.ast = parse_input(input); // ! WIP
		exec_input(&s); // ! make this
		// i = 0;
		//printf("content: %i", s.cmds->type);
		// TODO
		// if s.cmds.type = {EXEC, REDIR, PIPE}
		// cast s.cmds.type into
		// (t_exec*)s->cmds || (t_redir*)s->cmds || (t_pipe*)s->cmds
		// ! and so on
		// ? F5 para correr debug, breakpoint at line 60/61
		// ? check debugger screenshot on reference folder for expressions to watch
		// while (s.cmds[i] != NULL)
		// {
		// 	i++;
		// }
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
