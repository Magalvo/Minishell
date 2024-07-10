/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:22:12 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/10 16:56:14 by dde-maga         ###   ########.fr       */
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

void fd_unlock(t_cmd *cmd, t_ms *s, int *fd, int rd_only)
{
    (void)rd_only;
    if (chdir(cmd->file) == 0)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(cmd->file, 2);
        ft_putstr_fd(": ", 2);
        ft_putstr_fd("is a directory\n", 2);
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
