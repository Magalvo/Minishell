/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:25:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/04 22:43:06 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* void	minishell(char **envp)
{
	t_ms	s;
	char	*input;

	init_t_ms(&s);
	if (!init_minishell(&s, envp))
		exit_minishell(&s, NULL);
	while (true)
	{
		check_signal(MAIN);

		test loop
		if (isatty(fileno(stdin)))
		{
			input = readline(s.prompt);
			shell->prompt = readline(shell->terminal_prompt);
		}
		else
		{
			char *line;
			line = get_next_line(fileno(stdin));
			input = ft_strtrim(line, "\n");
			free(line);
		}
		end test loop

		regular readline function
		input = readline(s.prompt);
		tster ??? input = ft_strtrim(line, "\n");
		if (input == NULL && s.modal == MAIN)
			exit_minishell(&s, "exit\n");
		s.ast = parse_input(input, &s);
		if (!s.bnf && s.ast != NULL)
			exec_from_ast(&s);
		else if (s.ast != NULL)
		{
			s.bnf = false;
			print_ast(&s, s.ast, -1);
		}
		free(input);
		reset_ast(&s);
	}
	exit_minishell(&s, NULL);
} */


void minishell(char **envp)
{
	t_ms s;
	char *input;

	init_t_ms(&s);
	if (!init_minishell(&s, envp))
		exit_minishell(&s, NULL);
	while (true)
	{
		check_signal(MAIN);
		// Test loop
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

		input = readline(s.prompt);
		s.ast = parse_input(input, &s);
		if (input == NULL && s.modal == MAIN)
		{
			// Ensure proper exit code is set before exiting
			exit_minishell(&s, "exit\n");
			// Ensure exit with code 0 if this point is reached
		}
		if (!s.bnf && s.ast != NULL)
		{
			exec_from_ast(&s);
		}
		else if (s.ast != NULL)
		{
			s.bnf = false;
			print_ast(&s, s.ast, -1);
		}
		free(input);
		reset_ast(&s);
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
