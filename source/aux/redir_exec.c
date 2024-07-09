/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:22:12 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/09 15:15:27 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	exec_redir(t_ms *s, t_cmd *cmd, int fd_in, int fd_out)
// {
// 	int	temp_fd;

// 	temp_fd = -1;
// 	while (cmd->type == REDIR || cmd->type == HEREDOC)
// 	{
// 		if (cmd->type == HEREDOC)
// 			fd_in = cmd->fd;
// 		else if (cmd->fd == 1)
// 		{
// 			if (fd_out == STDOUT_FILENO)
// 				fd_unlock(cmd, s, &fd_out, 0);
// 			else
// 				ft_unlock_close(cmd, s, &temp_fd, 0);
// 		}
// 		else if (cmd->fd == 0)
// 		{
// 			if (fd_in == STDIN_FILENO)
// 				ft_unlock_close(cmd, s, &temp_fd, 1);
// 			else
// 				fd_unlock(cmd, s, &temp_fd, 1);
// 		}
// 		cmd = cmd->cmd;
// 	}
// 	if ((*cmd->argv))
// 		updating_cmds(s, cmd, cmd->argv[cmd->argc - 1]);
// 	exec_redir_fork(s, cmd, fd_in, fd_out);
// }


// backup b4 norminette
void	exec_redir(t_ms *s, t_cmd *cmd, int fd_in, int fd_out)
{
	int	temp_fd;

	temp_fd = -1;
	while (cmd->type == REDIR || cmd->type == HEREDOC)
	{
		if (cmd->type == HEREDOC)
			fd_in = cmd->fd;
		else if (cmd->fd == 1)
		{
			if (fd_out == STDOUT_FILENO)
				fd_unlock(cmd, s, &fd_out, 0);
			else
			{
				fd_unlock(cmd, s, &temp_fd, 0);
				close_fd(&temp_fd);
			}
		}
		else if (cmd->fd == 0)
		{
			if (fd_in == STDIN_FILENO)
			{
				fd_unlock(cmd, s, &fd_in, 1);
				close_fd(&temp_fd);
			}
			else
				fd_unlock(cmd, s, &temp_fd, 1);
		}
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
		if (fd_in != STDIN_FILENO)
			dup_and_close(s, fd_in, STDIN_FILENO);
		if (fd_out != STDOUT_FILENO)
			dup_and_close(s, fd_out, STDOUT_FILENO);
		exec_from_ast_recursive(s, cmd, STDIN_FILENO, STDOUT_FILENO);
		//s->exit_stat = 0;
		exit_minishell(s, NULL);
	}
	else
	{
		close_two_fd(cmd, fd_in, fd_out);
		wait_till_end(s, pid, cmd);
	}
}

/* 	//close_fd(&temp_fd);
	if ((*cmd->argv))
	{
		updating_cmds(s, cmd, cmd->argv[cmd->argc - 1]);
	}
	if (temp_fd < 0)
	{
		close_fd(&temp_fd);
		exec_redir_fork(s, cmd, fd_in, fd_out);
	}
	else
	{
		fd_in = temp_fd;
		close_fd(&temp_fd);
		exec_redir_fork(s, cmd, fd_in, fd_out);
	}
} */
