/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:25:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/06/27 18:24:26 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_minishell(t_ms *s, char *msg)
{
	int	exiter;

	if (!s)
		return ;
	exiter = s->exit_stat;
	if (msg)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
	}
	close_fd(&(s->infile));
	close_fd(&(s->outfile));
	if (s->env)
		free_env_list(s->env);
	if (s->export)
		free_env_list(s->export);
	if (s->ast != NULL)
	{
		free_ast(s->ast);
		s->ast = NULL;
	}
	cleanup_shell(s);
	exit(exiter);
}

int	init_minishell(t_ms *s, char **ep)
{
	int i = 0;	//! just for test
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
	init_list(&s->env, ep);
	init_list(&s->export, ep);
	env_paths(s, ep);
	s->env_tmp = env_convert(s->export);
	s->modal = MAIN;
	s->cmd_temp = NULL;
	s->prompt = "\e[3;33mnanoshell\e[0m\e[1;97m -> \e[0m";  // v alpha
	// s->prompt = "\e[3;33mnanoshell\e[0m\e[1;97m -> \e[0m";    // v beta
	// s->prompt = "\e[3;33mminishell\e[0m\e[1;97m -> \e[0m";     // v gold
	return (true);
}

void	init_t_ms(t_ms *s)
{
	s->prompt = NULL;
	s->paths = NULL;
	s->username = NULL;
	s->modal = -1;
	s->infile = -1;
	s->outfile = -1;
	s->input_empty = false;
	s->bnf = false;
	s->env_tmp = NULL;
	s->cmd_temp = NULL;
	s->ast = NULL;
	s->env = NULL;
	s->export = NULL;
	s->exit_stat = 0;
}

void	reset_ms(t_ms *s, char *input, int error)
{
	if (error >= 0)
		s->exit_stat = error;
	free(input);
}
