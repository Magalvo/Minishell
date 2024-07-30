/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:22:12 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/30 18:56:51 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_two_fd(t_cmd *cmd, int fd_in, int fd_out)
{
	(void)cmd;
	if (fd_in != STDIN_FILENO)
		close_fd(&fd_in);
	if (fd_out != STDOUT_FILENO)
		close_fd(&fd_out);
}

void	fd_errors(t_ms *s, t_cmd *cmd)
{
	(void)cmd;
	if (access(cmd->file, F_OK) == -1)
		s->exit_stat = 1;
	else
		s->exit_stat = 2;
	perror(cmd->file);
}

void	fd_unlock(t_cmd *cmd, t_ms *s, int *fd, int rd_only)
{
	(void)rd_only;
	if (chdir(cmd->file) == 0)
	{
		ft_dprintf(2, "minishell: %s : Is a directory\n", cmd->file);
		s->exit_stat = 1;
		return ;
	}
	if (rd_only == 0)
	{
		*fd = open(cmd->file, cmd->mode, 0666);
		if (*fd < 0)
			fd_errors(s, cmd);
	}
	else if (rd_only == 1)
	{
		*fd = open(cmd->file, O_RDONLY);
		if (*fd < 0)
			fd_errors(s, cmd);
	}
}

void	ft_unlock_close(t_cmd *cmd, t_ms *s, int *fd, int rd_only)
{
	fd_unlock(cmd, s, fd, rd_only);
	close_fd(fd);
}
