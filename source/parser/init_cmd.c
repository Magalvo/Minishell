/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:06:42 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/09/05 10:58:33 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*cmd_init(t_ms *s)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		ft_dprintf(STDERR_FILENO, "%s\n", EXEC_MISSING_CMD);
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

t_cmd	*cmd_redir_out(t_cmd *subcmd, char *filename, int mode, t_ms *s)
{
	t_cmd	*cmd;

	cmd = cmd_init(s);
	cmd->type = REDIR;
	cmd->cmd = subcmd;
	unglue_str(filename, filename + ft_strlen(filename));
	filename = expand_sw_vars(filename, s);
	filename = reassemble_input(filename);
	str_rm_char(filename, EMPTY);
	cmd->file = filename;
	cmd->mode = mode;
	cmd->fd = 1;
	return (cmd);
}

t_cmd	*cmd_redir_in(t_cmd *subcmd, char *filename, int mode, t_ms *s)
{
	t_cmd	*cmd;

	cmd = cmd_init(s);
	cmd->type = REDIR;
	cmd->cmd = subcmd;
	unglue_str(filename, filename + ft_strlen(filename));
	filename = expand_sw_vars(filename, s);
	filename = reassemble_input(filename);
	str_rm_char(filename, EMPTY);
	cmd->file = filename;
	cmd->mode = mode;
	cmd->fd = 0;
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
