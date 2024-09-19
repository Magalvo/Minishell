/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:24:23 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/09/19 18:58:26 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_from_ast_recursive(t_ms *s, t_cmd *cmd, int fd_in, int fd_out)
{
	if (!cmd)
		return ;
	if (cmd->type == EXEC)
	{
		aux_rec_exec(s, cmd, fd_in, fd_out);
	}
	else if (cmd->type == PIPE)
	{
		exec_pipe(s, cmd, fd_in, fd_out);
	}
	else if (cmd->type == REDIR || cmd->type == HEREDOC)
	{
		if (fd_in != STDIN_FILENO && cmd->fd == 0 && s->ast->type == PIPE)
		{
			dprintf(2, "\nVISTA ALEGRE\n");
			fd_in = STDIN_FILENO;
		}
		/* if (cmd->error_msg != NULL)
			ft_dprintf(2, "%s\n",cmd->error_msg); */
		exec_redir(s, cmd, fd_in, fd_out);
	}
}

void	standard_check(t_ms *s, int fd_in, int pipefd)
{
	if (fd_in != STDIN_FILENO)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			close(fd_in);
			close(pipefd);
			exit_minishell(s, "dup2");
		}
	}
	if (pipefd != STDOUT_FILENO)
	{
		if (dup2(pipefd, STDOUT_FILENO) == -1)
		{
			close(fd_in);
			close(pipefd);
			exit_minishell(s, "dup2");
		}
	}
}

// TODO check line 74, solves double free. causes problem?
void	exec_pipe(t_ms *s, t_cmd *cmd, int fd_in, int fd_out)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		perror("!!!!PIPEFD!!!!");
	pid = fork1();
	if (pid == 0)
	{
		close(pipefd[0]);
		standard_check(s, fd_in, pipefd[1]);
		close(pipefd[1]);
		exec_from_ast_recursive(s, cmd->left, fd_in, STDOUT_FILENO);
		close_two_fd(cmd, fd_in, fd_out);
		exit_minishell(s, NULL);
	}
	else
	{
		if (close(pipefd[1]) == 0 && fd_in != STDIN_FILENO)
			close_fd(&fd_in);
		if (cmd->left->fd > 2)
			close_fd(&cmd->left->fd);
		exec_from_ast_recursive(s, cmd->right, pipefd[0], fd_out);
		wait_till_end(s, pid, cmd);
		close(pipefd[0]);
	}
}

int	not_found(char *str, int status, t_ms *s)
{
	char	*temp;

	if (!str)
		return (1);
	temp = str;
	if (temp)
		ft_putstr_fd(temp, 2);
	if (status == 127)
	{
		if ((str[0] == '.' && str[1] == '/') || str[0] == '/')
		{
			if (is_dir(str))
			{
				s->exit_stat = 126;
				ft_putstr_fd(" : Is a directory\n", 2);
			}
			else if (!is_dir(str) && (str[0] == '/' || str[0] == '.'))
				ft_putstr_fd(" : No such file or directory\n", 2);
		}
		else
			ft_putstr_fd(" : command not found\n", 2);
	}
	else if (status == 126)
		return (ft_putstr_fd(" : Permission denied\n", 2), 126);
	return (1);
}

void	exit_and_found(char *str, int status, t_ms *s)
{
	s->exit_stat = status;
	if (not_found(str, status, s) == 126)
		return ;
}
