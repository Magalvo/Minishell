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

void exec_redir(t_ms *s, t_cmd *cmd, int fd_in, int fd_out)
{
    t_cmd *current = cmd;

    while (current && current->type != EXEC)
    {
        if (current->type == HEREDOC)
        {
            fd_in = current->fd;
        }
        else if ((current->mode & O_WRONLY) || (current->mode & O_RDWR))
        {
            fd_out = open(current->file, current->mode, 0666);
            if (fd_out < 0)
            {
                s->exit_stat = 1;
                perror("open");
                return;
            }
        }
        else if (current->file)
        {
            fd_in = open(current->file, O_RDONLY);
            if (fd_in < 0)
            {
                s->exit_stat = 1;
                perror("open");
                return;
            }
        }
        current = current->cmd; // Move to the nested command
    }

    if (current && current->type == EXEC)
    {
        exec_redir_fork(s, current, fd_in, fd_out);
    }
}

void exec_redir_fork(t_ms *s, t_cmd *cmd, int fd_in, int fd_out)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        if (fd_in != STDIN_FILENO)
            dup_and_close(fd_in, STDIN_FILENO);
        if (fd_out != STDOUT_FILENO)
            dup_and_close(fd_out, STDOUT_FILENO);

        exec_from_ast_recursive(s, cmd, STDIN_FILENO, STDOUT_FILENO);
        exit(s->exit_stat);
    }
    else
    {
        close_two_fd(cmd, fd_in, fd_out);
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            s->exit_stat = WEXITSTATUS(status);
    }
}

void	close_two_fd(t_cmd *cmd, int fd_in, int fd_out)
{
	(void)cmd;
	if (fd_in != STDIN_FILENO)    //!! && cmd->file
		close(fd_in);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
}
