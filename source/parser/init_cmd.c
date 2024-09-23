/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:06:42 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/09/19 21:08:27 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*cmd_init(t_ms *s)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		reprompt(EXEC_MISSING_CMD, 2, s);
	cmd->error_msg = NULL;
	cmd->inv_file = 0;
	return (cmd);
}

t_cmd	*cmd_exec(t_ms *s)
{
	t_cmd	*cmd;

	cmd = cmd_init(s);
	if (!cmd)
		return (NULL);
	cmd->type = EXEC;
	cmd->argc = 0;
	cmd->argv = NULL;
	return (cmd);
}

t_cmd	*cmd_pipe(t_cmd *left, t_cmd *right, t_ms *s)
{
	t_cmd	*cmd;

	cmd = cmd_init(s);
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return (cmd);
}
