/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:06:42 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/05 19:31:54 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*cmd_init(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	return (cmd);
}

t_cmd	*cmd_exec(void)
{
	t_cmd	*cmd;

	cmd = cmd_init();
	if (!cmd)
		return (NULL);
	cmd->type = EXEC;
	cmd->argc = 0;
	cmd->argv = NULL;
	return (cmd);
}

t_cmd	*cmd_redir(t_cmd *subcmd, char *filename, int mode, int fd)
{
	t_cmd	*cmd;

	cmd = cmd_init();
	cmd->type = REDIR;
	cmd->cmd = subcmd;
	unglue_str(filename, filename + ft_strlen(filename));
	filename = reassemble_input(filename);
	cmd->file = filename;
	cmd->mode = mode;
	cmd->fd = fd;
	return (cmd);
}

t_cmd	*cmd_pipe(t_cmd *left, t_cmd *right)
{
	t_cmd	*cmd;

	cmd = cmd_init();
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return (cmd);
}
