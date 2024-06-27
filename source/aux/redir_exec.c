/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:22:12 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/06/27 14:22:41 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_redir(t_ms *s, t_cmd *cmd, int fd_in, int fd_out)
{
	pid_t	pid;
	int		status;

	if (cmd->type == HEREDOC)
		fd_in = cmd->fd;
	else if ((cmd->mode & O_WRONLY || cmd->mode & O_RDWR))
	{
		fd_out = open(cmd->file, cmd->mode, 0666);
		if (fd_out < 0)
		{
			s->exit_stat = 1;
			return (perror("open"));
		}
	}
	else if (cmd->file)
	{
		fd_in = open(cmd->file, O_RDONLY);
		if (fd_in < 0)
		{
			s->exit_stat = 1;
			return (perror("open"));
		}
	}
	pid = fork();
	if (pid == -1)
		error_msg("fork");
	else if (pid == 0)
	{
		if (fd_in != STDIN_FILENO)
			dup_and_close(fd_in, STDIN_FILENO);
		if (fd_out != STDOUT_FILENO)
			dup_and_close(fd_out, STDOUT_FILENO);
		if (cmd->cmd->type == EXEC)
			exec_from_ast_recursive(s, cmd->cmd, STDIN_FILENO, STDOUT_FILENO);
		else
			exec_from_ast_recursive(s, cmd->cmd, STDIN_FILENO, fd_out);
		exit(s->exit_stat);
	}
	else
	{
		if (fd_in != STDIN_FILENO && cmd->file)
			close(fd_in);
		if (fd_out != STDOUT_FILENO)
			close(fd_out);
		waitpid(pid, &status, 0);
		//printf("REDIR-> %d\n", status);
		if (WIFEXITED(status))
			s->exit_stat = WEXITSTATUS(status);
	}
}
