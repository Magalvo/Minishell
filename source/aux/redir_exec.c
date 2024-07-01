/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:22:12 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/06/28 20:13:10 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	fd_errors(t_ms *s, t_cmd *cmd)
{
    (void)cmd;
   // printf("%s\n", s->ast->cmd->argv[0]);
	s->exit_stat = 1;
	perror(s->ast->cmd->argv[0]);
	return ;
}

void	fd_unlock(t_cmd *cmd, t_ms *s, int *fd, int rd_only)
{
	if (rd_only == 1)
	{
		*fd = open(cmd->file, O_RDONLY);
		if (*fd < 0)
            fd_errors(s, cmd);
	}
	else
	{
		*fd = open(cmd->file, cmd->mode, 0666);
		if (*fd < 0)
        {
            fd_errors(s, cmd);
        }
	}
}

void exec_redir(t_ms *s, t_cmd *cmd, int fd_in, int fd_out)
{
    while (cmd->type == REDIR || cmd->type == HEREDOC)
    {
		int	temp_fd;

		temp_fd = -1;
        if (cmd->type == HEREDOC)
            fd_in = cmd->fd;
        else if (cmd->mode & O_WRONLY || cmd->mode & O_RDWR)
        {
            if (fd_out == STDOUT_FILENO)
				fd_unlock(cmd, s, &fd_out, 0);
            else
			{
				fd_unlock(cmd, s, &temp_fd, 0);
				close(temp_fd);
			}
        }
        else if (cmd->file)
			fd_unlock(cmd, s, &fd_in, 1);
        cmd = cmd->cmd;
    }
    updating_cmds(s, cmd, cmd->argv[cmd->argc - 1]);
    exec_redir_fork(s, cmd, fd_in, fd_out);
}

void exec_redir_fork(t_ms *s, t_cmd *cmd, int fd_in, int fd_out)
{
    pid_t pid;

    pid = fork1();
    if (pid == 0)
    {
        if (fd_in != STDIN_FILENO)
            dup_and_close(s, fd_in, STDIN_FILENO);
        if (fd_out != STDOUT_FILENO)
            dup_and_close(s, fd_out, STDOUT_FILENO);
        if (cmd->type == EXEC)
            exec_from_ast_recursive(s, cmd, STDIN_FILENO, STDOUT_FILENO);
        else
            exec_from_ast_recursive(s, cmd, STDIN_FILENO, fd_out);
        exit(s->exit_stat);
    }
    else
    {
        close_two_fd(cmd, fd_in, fd_out);
		wait_till_end(s, pid);
    }
}

void	close_two_fd(t_cmd *cmd, int fd_in, int fd_out)
{
	(void)cmd;
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
}
