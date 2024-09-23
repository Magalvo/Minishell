/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:15:46 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/09/20 10:21:06 by dde-maga         ###   ########.fr       */
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
	t_cinfo	cinfo;

	cinfo = cmd_info(NULL, 0);
	if (s->exit_stat != 130)
	{
		close(heredoc);
		free_ast(cmd);
		if (s->cmd_temp != NULL)
			free(s->cmd_temp);
		free_cmdinfo(&cinfo);
		clear_fds();
		exit_minishell(s, NULL);
	}
	else
	{
		close(heredoc);
		free_ast(cmd);
		if (s->cmd_temp != NULL)
			free(s->cmd_temp);
		free_cmdinfo(&cinfo);
		clear_fds();
		exit_minishell(s, NULL);
	}
}

void	close_fd_child(t_cmd *cmd, int fd_in, int fd_out)
{
	(void)cmd;
	close_fd(&fd_in);
	close_fd(&fd_out);
}

int	check_read_acess(t_cmd *cmd_h, t_ms *s)
{
	if (access(cmd_h->file, F_OK | R_OK) != 0)
	{
		s->exit_stat = 1;
		perror(cmd_h->file);
		return (1);
	}
	return (0);
}
