/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:25:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/30 18:56:02 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// ! WTF? debug right?
// void print_open_fds(void)
// {
// 	char path[256];
// 	snprintf(path, sizeof(path), "/proc/%d/fd", getpid());
// 	DIR *dir = opendir(path);
// 	if (dir) {
// 		struct dirent *entry;
// 		while ((entry = readdir(dir)) != NULL) {
// 			if (entry->d_type == DT_LNK) {
// 				printf("Open FD: %s\n", entry->d_name);
// 			}
// 		}
// 		closedir(dir);
// 	}
// }

		/* Test loop */
		// if (isatty(fileno(stdin)))
		// {
		// 	input = readline(s.prompt);
		// }
		// else
		// {
		// 	char *line;
		// 	line = get_next_line(fileno(stdin));
		// 	input = ft_strtrim(line, "\n");
		// 	free(line);
		// }

// todo line 68 comment
void	minishell(char **envp)
{
	t_ms	s;
	char	*input;

	init_t_ms(&s);
	if (!init_minishell(&s, envp))
		exit_minishell(&s, NULL);
	while (true)
	{
		check_signal(MAIN);
		input = readline(s.prompt);
		s.ast = parse_input(&input, &s);
		if (input == NULL && s.modal == MAIN)
			exit_minishell(&s, "exit\n");
		if (!s.bnf && s.ast != NULL)
			exec_from_ast(&s);
		else if (s.ast != NULL)
		{
			s.bnf = false;
			print_ast(&s, s.ast, -1);
		}
		//print_open_fds();
		free(input);
		reset_ast(&s);
	}
	rl_clear_history();
	exit_minishell(&s, NULL);
}

int	main(int argc, char *argv[], char *envp[])
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
