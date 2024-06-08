// header goes here

#include "../include/minishell.h"

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

/* char **set_min_env(void)
{
	char	**temp;
	char	*env;
	// TODO env output when: env -i bash
	// PWD=/home/kajo	//? hmm, donoo
	// SHLVL=1		// ! this one is easy
	// PATH=/home/kajo/.local/bin/:/usr/local/bin:/usr/bin
	// forced PATH: /home/kajo/.local/bin/
	//				/usr/local/bin
	//				/usr/bin
	// ! true on fedora, maybe not on ubuntu: /usr/bin might be /bin
	// _=/usr/bin/env			// < last command
	// s->env_tmp
	temp = ft_calloc((5), sizeof(char *));
	env = ft_calloc(14 + 1, sizeof(char));
	env = "PWD=/home/kajo\0";
	temp[0] = env;
	// or something like it
	return (temp);
 } */


int init_minishell(t_ms *s, char **ep)
{
	int i = 0;  //! just for test
	if (!*ep)
	{
		initialize_env(&ep);
		while (ep[i])
		{
			printf("%s\n", ep[i]);
			i++;
		}
		//exit_minishell(s, NULL);
	}
	init_env(s, ep);
	init_export(s, ep);
	env_paths(s, ep);
	s->env_tmp = ep;				//! added raw env for execve
	s->modal = MAIN;
	s->cmd_temp = NULL;
	// s->prompt = "write_here ->";    // v zero
	s->prompt = "\e[3;33mnanoshell\e[0m\e[1;97m -> \e[0m";  // v alpha
	// s->prompt = "\e[3;33mnanoshell\e[0m\e[1;97m -> \e[0m";    // v beta
	// s->prompt = "\e[3;33mminishell\e[0m\e[1;97m -> \e[0m";     // v gold
	return (true);
}

//!!!!!!!!!! O MINIHELL TEM DE SUBIR 1 NIVEL ASSIM QUE INICIA a nao ser que seja sem env

void	init_t_ms(t_ms *s)
{
	// s = ft_calloc(sizeof(t_ms), sizeof(t_ms));
	s->prompt = NULL;
	s->paths = NULL;
	s->username = NULL;
	s->modal = -1;
	s->infile = -1;
	s->outfile = -1;
	s->input_empty = NULL;
	s->env_tmp = NULL;
	s->cmd_temp = NULL;
	s->ast = NULL;
	s->env = NULL;
	s->export = NULL;
}


// STATUS: signal caught, ctrl+\ shouldn't print to stdout
void minishell(char **envp)
{
	t_ms	s;

	init_t_ms(&s);
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
		s.ast = parse_input(input); // ! WIP
		// todo:
		// double input display on parse error (ast == NULL)
		// on ast NULL break execution,
		exec_input(&s); // ! make this
		// maybe make this functions depend on exec status
		// dont need to run if exec didnt execute (no changes)
		env_arr_update(&s);
		env_paths(&s, s.env_tmp);
		// TODO
		free(input);
	}
	exit_minishell(&s, NULL);
}

int main(int argc, char *argv[], char *envp[])
{
	(void)argv;

	if (argc != 1)
		return (ft_dprintf(STDERR_FILENO, \
			"Minishell takes no arguments, Exiting.\n"));
	if (!*envp)
		ft_dprintf(STDERR_FILENO, \
			"Naughty naughty evALuaTOr... hmmff!\n");
	minishell(envp);
	return (0);
}
