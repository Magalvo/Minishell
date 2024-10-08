/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:06:42 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/09/20 10:53:40 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cmd_redir(t_cmd *cmd, char *filename, int mode)
{
	cmd->type = REDIR;
	cmd->mode = mode;
	cmd->file = filename;
}

t_cmd	*cmd_redir_out(t_cmd *subcmd, char *filename, int mode, t_ms *s)
{
	t_cmd	*cmd;
	char	*end_file;
	bool	filename_expand;

	filename_expand = false;
	cmd = cmd_init(s);
	cmd->cmd = subcmd;
	unglue_str(filename, filename + ft_strlen(filename));
	filename = expand_sw_vars(filename, s);
	end_file = filename;
	get_endstr_ptr(&end_file);
	if (*filename == DQUOTE && *--end_file == DQUOTE)
		filename_expand = true;
	filename = reassemble_input(filename);
	end_file = filename;
	get_endstr_ptr(&end_file);
	if (peek_nsp(filename, end_file, SPACES))
		cmd->error_msg = REDIR_SYNTAX;
	if (filename_expand)
		cmd->error_msg = NULL;
	str_rm_char(filename, EMPTY);
	cmd->fd = 1;
	cmd_redir(cmd, filename, mode);
	return (cmd);
}

t_cmd	*cmd_redir_in(t_cmd *subcmd, char *filename, int mode, t_ms *s)
{
	t_cmd	*cmd;
	char	*end_file;
	bool	filename_expand;

	filename_expand = false;
	cmd = cmd_init(s);
	cmd->cmd = subcmd;
	unglue_str(filename, filename + ft_strlen(filename));
	filename = expand_sw_vars(filename, s);
	end_file = filename;
	get_endstr_ptr(&end_file);
	if (*filename == DQUOTE && *--end_file == DQUOTE)
		filename_expand = true;
	filename = reassemble_input(filename);
	end_file = filename;
	get_endstr_ptr(&end_file);
	if (peek_nsp(filename, end_file, SPACES))
		cmd->error_msg = REDIR_SYNTAX;
	if (filename_expand)
		cmd->error_msg = NULL;
	str_rm_char(filename, EMPTY);
	cmd->fd = 0;
	cmd_redir(cmd, filename, mode);
	return (cmd);
}

void	handle_new_arg(char **q, char **eq, t_ms *s, char **new_arg)
{
	*new_arg = ft_calloc((*eq - *q) + 1, sizeof(char));
	ft_memmove ((void *)*new_arg, (void *)*q, (*eq - *q));
	unglue_str (*new_arg, *new_arg + ft_strlen(*new_arg));
	*new_arg = expand_sw_vars(*new_arg, s);
}
