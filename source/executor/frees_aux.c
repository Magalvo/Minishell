/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:15:46 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/09/10 00:02:53 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free2(char *one, char *two)
{
	if (one)
	{
		free(one);
		one = NULL;
	}
	if (two)
	{
		free(two);
		two = NULL;
	}
}

void	exit_doc(t_ms *s, int heredoc, t_cmd *cmd)
{
	(void)cmd;
	if (s->exit_stat != 130)
	{
		free_ast(s->cmd_temp2);
		free_ast2(&cmd->cmd);
		free_ast2(&cmd);
		if (s->cmd_temp != NULL)
		{
			free(s->cmd_temp);
			s->cmd_temp = NULL;
		}
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
		exit(del_eof(heredoc));
	}
	else
	{
		close(heredoc);
		free_ast2(&cmd->cmd);
		free_ast2(&cmd);
		if (s->cmd_temp != NULL)
		{
			free(s->cmd_temp);
			s->cmd_temp = NULL;
		}
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
		s->error = true;
		exit(130);
	}
}

void	close_fd_child(t_cmd *cmd, int fd_in, int fd_out)
{
	(void)cmd;
	close_fd(&fd_in);
	close_fd(&fd_out);
}


/* void	exit_doc(t_ms *s, int heredoc, t_cmd *cmd)
{
	(void)cmd;
	if (s->exit_stat != 130)
	{
		del_eof(heredoc);
		free_herechild(&cmd);
		if (s->cmd_temp != NULL)
		{
			free(s->cmd_temp);
			s->cmd_temp = NULL;
		}
		exit_minishell(s, NULL);
	}
	else
		close(heredoc);
} */