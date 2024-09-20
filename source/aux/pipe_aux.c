/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:20:18 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/09/19 18:58:51 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_empty_arg(t_cmd *cmd)
{
	int	i;

	free(cmd->argv[0]);
	i = 0;
	while (cmd->argv[i + 1] != NULL)
	{
		cmd->argv[i] = cmd->argv[i + 1];
		i++;
	}
	cmd->argv[i] = NULL;
	cmd->argc -= 1;
}

void	check_update_cmds(t_ms *s, t_cmd *cmd, int fd_in, int fd_out)
{
	if (cmd && cmd->argc > 0)
		updating_cmds(s, cmd, cmd->argv[cmd->argc -1]);
	if (!builtins_parent(s, cmd->argv, fd_in, fd_out))
		single_exec(s, cmd, fd_in, fd_out);
}

void	aux_rec_exec(t_ms *s, t_cmd *cmd, int fd_in, int fd_out)
{
	if (cmd->argv && cmd->argv[0])
	{
		if (cmd->argv[0][0] == EMPTY)
		{
			handle_empty_arg(cmd);
		}
		else if ((ft_isspace(cmd->argv[0][0]) && cmd->argv[0][0] == '\0' && \
					!cmd->argv[1]) || cmd->argv[0][0] == '\0')
		{
			exit_and_found(cmd->argv[0], 127, s);
			return ;
		}
	}
	check_update_cmds(s, cmd, fd_in, fd_out);
}

bool	check_argv(t_cmd *cmd)
{
	if (!cmd)
		return (false);
	if (cmd->left)
		check_argv(cmd->left);
	if (cmd->right)
		check_argv(cmd->right);
	if (cmd->cmd)
		check_argv(cmd->cmd);
	if (cmd->type == EXEC && !cmd->argv[0])
		return (false);
	return (true);
}

void	exec_from_ast(t_ms *s)
{
	int	i;

	i = 3;
	if (!s->ast || !check_argv(s->ast) || s->error == true)
	{
		while (i < FD_MAX)
		{
			close(i);
			i++;
		}
		return ;
	}
	if (!ft_exec_paria(s, s->ast))
	{
		exec_from_ast_recursive(s, s->ast, STDIN_FILENO, STDOUT_FILENO);
		s->wait = 0;
	}
}
