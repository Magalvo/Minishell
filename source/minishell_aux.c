/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:25:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/09/25 11:04:50 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_minishell(t_ms *s, char *msg)
{
	int				exiter;
	unsigned char	res;

	if (!s)
		return ;
	exiter = s->exit_stat;
	if (msg)
	{
		ft_putstr_fd(msg, 1);
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
	clear_history();
	res = (unsigned char)exiter;
	exit(res);
}

int	init_minishell(t_ms *s, char **ep)
{
	char	*shell;

	if (!*ep)
	{
		initialize_env(&ep);
	}
	init_list(&s->env, ep);
	init_list(&s->export, ep);
	env_paths(s, ep);
	s->env_tmp = env_convert(s->export);
	s->modal = MAIN;
	s->cmd_temp = NULL;
	s->prompt = "minishell> ";
	shell = get_env_val(s->env, "SHELL", s);
	if (shell != NULL)
	{
		update_key(s->env, "SHELL", "./minishell");
		free(shell);
	}
	exit_pack(s, NULL);
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
	s->exit_stat = 0;
	s->input = NULL;
	s->wait = 0;
	s->error = false;
	s->input_empty = false;
	s->bnf = false;
	s->env_tmp = NULL;
	s->cmd_temp = NULL;
	s->cmd_temp2 = NULL;
	s->cmd_carris = NULL;
	s->file_err = 0;
	s->ast = NULL;
	s->env = NULL;
	s->export = NULL;
}

void	reset_ms(t_ms *s, char *input, int error)
{
	if (error >= 0)
		s->exit_stat = error;
	free(input);
}

void	clear_fds(void)
{
	int	i;

	i = 3;
	while (i < FD_MAX)
	{
		close(i);
		i++;
	}
}
