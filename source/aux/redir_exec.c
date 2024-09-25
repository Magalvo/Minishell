/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:22:12 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/09/25 11:00:24 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	unclose1(t_ms *s, t_cmd *cmd, int *fd_out, int *temp_fd)
{
	if (s->file_err > 0 && cmd->inv_file != 1)
		return ;
	else if (cmd->inv_file == 1)
		s->file_err -= 1;
	if (*fd_out == STDOUT_FILENO)
		fd_unlock(cmd, s, fd_out, 0);
	else
		ft_unlock_close(cmd, s, temp_fd, 0);
}

void	unclose0(t_ms *s, t_cmd *cmd, int *fd_in, int *temp_fd)
{
	if (*fd_in == STDIN_FILENO)
	{
		fd_unlock(cmd, s, fd_in, 1);
		close_fd(temp_fd);
	}
	else
	{
		close_fd(temp_fd);
		fd_unlock(cmd, s, temp_fd, 1);
	}
}

void	exec_redir(t_ms *s, t_cmd *cmd, int fd_in, int fd_out)
{
	int	temp_fd;

	temp_fd = -1;
	if (aux_verify(cmd, s) == 1)
		return ;
	while (cmd->type == REDIR || cmd->type == HEREDOC)
	{
		if (cmd->error_msg)
		{
			ft_dprintf(2, "%s\n", cmd->error_msg);
			return ;
		}
		heredoc_handler(s, cmd, &fd_in, &temp_fd);
		if (cmd->fd == 0)
			unclose0(s, cmd, &fd_in, &temp_fd);
		else if (cmd->fd == 1)
			unclose1(s, cmd, &fd_out, &temp_fd);
		cmd = cmd->cmd;
	}
	close_fd(&temp_fd);
	if ((*cmd->argv))
		updating_cmds(s, cmd, cmd->argv[cmd->argc - 1]);
	exec_redir_fork(s, cmd, fd_in, fd_out);
}

void	exec_redir_fork(t_ms *s, t_cmd *cmd, int fd_in, int fd_out)
{
	pid_t	pid;

	pid = fork1();
	if (pid == 0)
	{
		s->exit_stat = 0;
		if (fd_in != STDIN_FILENO)
		{
			dup_and_close(s, &fd_in, &fd_out, STDIN_FILENO);
		}
		if (fd_out != STDOUT_FILENO)
		{
			dup_and_close(s, &fd_out, &fd_in, STDOUT_FILENO);
		}
		exec_from_ast_recursive(s, cmd, STDIN_FILENO, STDOUT_FILENO);
		clear_fds();
		exit_minishell(s, NULL);
	}
	else
	{
		clear_fds();
		close_two_fd(cmd, fd_in, fd_out);
		wait_till_end(s, pid, cmd);
	}
}

void	free_cmdinfo(t_cinfo *cinfo)
{
	int	i;

	i = 0;
	if (cinfo->cmd[i] != NULL)
	{
		while (cinfo->cmd[i] != NULL)
		{
			free_ast2(&cinfo->cmd[i]);
			cinfo->cmd[i] = NULL;
			i++;
		}
	}
}
