/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:24:23 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/06/26 19:02:11 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* void	aux_pipe_child(t_ms *s, t_cmd *cmd, int *pipefd, int fd_in)
{
	
}*/

/* void	aux_pipe_parent(t_ms *s, pid_t pid, int *pipefd, int fd_out)
{
	close(pipefd[1]);
	exec_from_ast_recursive(s, s->ast->right, pipefd[0], fd_out);
	close(pipefd[0]);
	wait_till_end(s, pid);
}*/

void	exec_from_ast_recursive(t_ms *s, t_cmd *cmd, int fd_in, int fd_out)
{
	int		pipefd[2];
	pid_t	pid;

    if (!cmd)
        return ;
    if (cmd->type == EXEC)
		aux_rec_exec(s, cmd, fd_in, fd_out);
    else if (cmd->type == PIPE)
    {
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
			free_ast(cmd);
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
    else if (cmd->type == REDIR || cmd->type == HEREDOC)
	{
		updating_cmds(s, NULL);
		exec_redir(s, cmd, fd_in, fd_out);
	}	
}

void	free_ast(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	free_ast(cmd->left);
	free_ast(cmd->right);
	free_ast(cmd->cmd);
	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i])
			free(cmd->argv[i++]);
		free(cmd->argv);
	}
	if (cmd->file)
		free(cmd->file);
	if (cmd->delim)
		free(cmd->delim);
	if (cmd->temp)
	{
		i = 0;
		while (cmd->temp[i])
			free(cmd->temp[i++]);
		free(cmd->temp);
	}
	free(cmd);
}

void	reset_ast(t_ms *s)
{
	if (s->ast)
	{
		free_ast(s->ast);
		s->ast = NULL;
	}
}
