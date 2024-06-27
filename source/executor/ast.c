/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:24:23 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/06/27 19:29:09 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_from_ast_recursive(t_ms *s, t_cmd *cmd, int fd_in, int fd_out)
{
	if (!cmd)
		return ;
	if (cmd->type == EXEC)
		aux_rec_exec(s, cmd, fd_in, fd_out);
	else if (cmd->type == PIPE)
	{
		exec_pipe(s, cmd, fd_in, fd_out);
	}
	else if (cmd->type == REDIR || cmd->type == HEREDOC)
	{
		exec_redir(s, cmd, fd_in, fd_out);
	}
}

void	exec_pipe(t_ms *s, t_cmd *cmd, int fd_in, int fd_out)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		error_msg("pipe");
	pid = fork1();
	if (pid == 0)
	{
		close(pipefd[0]);
		if (fd_in != STDIN_FILENO)
			dup2(fd_in, STDIN_FILENO);
		if (pipefd[1] != STDOUT_FILENO)
			dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exec_from_ast_recursive(s, cmd->left, fd_in, STDOUT_FILENO);
		exit(s->exit_stat);
	}
	else
	{
		close(pipefd[1]);
		exec_from_ast_recursive(s, cmd->right, pipefd[0], fd_out);
		close(pipefd[0]);
		wait_till_end(s, pid);
	}
}

void	free_ast(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	if (cmd->left)
		free_ast(cmd->left);
	if (cmd->right)
		free_ast(cmd->right);
	if (cmd->cmd)
		free_ast(cmd->cmd);
	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i])
		{
			free(cmd->argv[i]);
			cmd->argv[i] = NULL;
			i++;
		}
		free(cmd->argv);
		cmd->argv = NULL;
	}
	if (cmd->file)
	{
		free(cmd->file);
		cmd->file = NULL;
	}
	if (cmd->delim)
		free(cmd->delim);
	/* free(cmd);
		cmd = NULL; */
}

void	reset_ast(t_ms *s)
{
	if (s->ast)
	{
		free_ast(s->ast);
		s->ast = NULL;
	}
}

int	not_found(char *str, int status, t_ms *s)
{
	ft_putstr_fd(str, 2);
	if(status == 127)
	{
		if(str[0] == '.' || str[0] == '/')
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			ft_putstr_fd(": command not found\n", 2);
	}
	if(status == 126)
		ft_putstr_fd(": permission denied\n", 2);
	ft_putnbr_fd(status, 2);
	ft_putstr_fd("\n", 2);
	return(set_exit(status, s), 1);
}
