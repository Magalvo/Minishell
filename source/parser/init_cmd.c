/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:06:42 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/06/29 14:45:47 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*cmd_init(void)
{
	t_cmd	*cmd;

	// cmd = ft_calloc(sizeof(*cmd), sizeof(*cmd));
	cmd = ft_calloc(1, sizeof(*cmd));
	return (cmd);
}

t_cmd *cmd_exec(void)
{
	t_cmd	*cmd;

	cmd = cmd_init();
	cmd->type = EXEC;
	cmd->argc = 0;
	cmd->argv = 0;
	return (cmd);
}

t_cmd *cmd_redir(t_cmd *subcmd, char *filename, int mode, int fd)
{
	t_cmd	*cmd;

	cmd = cmd_init();
	cmd->type = REDIR;
	cmd->cmd = subcmd;
	unglue_str(filename, filename + ft_strlen(filename));
	ft_strrep_range(filename, NULL, (char)17, '$');
	retokenizer(filename, filename + ft_strlen(filename));
	filename = remove_quotes(filename, filename);
	cmd->file = filename;
	cmd->mode = mode;
	cmd->fd = fd;
	return (cmd);
}

t_cmd *cmd_pipe(t_cmd *left, t_cmd *right)
{
	t_cmd *cmd;

	cmd = cmd_init();
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return (cmd);
}
