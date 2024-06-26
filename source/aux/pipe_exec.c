/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:42:53 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/06/28 16:59:11 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_one(t_ms *s, char **argv)
{
	char	*path;
	char	*cmd_name;

	if ((argv[0] && argv[0][0] == '/' && argv[0][1]) || \
		(argv[0] && argv[0][0] == '.' && argv[0][1] == '/' && argv[0][2]))
	{
		execve(argv[0], argv, s->env_tmp);
		not_found(argv[0], 127, s);
	}
	else if (argv && argv[0] != NULL)
	{
		path = cmd_path(s->paths, argv[0], s);
		if (!path)
			not_found(argv[0], 127, s);
		cmd_name = ft_strchr(argv[0], '/');
		if (cmd_name)
		{
			cmd_name++;
			argv[0] = cmd_name;
		}
		execve(path, argv, s->env_tmp);
		free(path);
		set_exit(126, s);
	}
}

int	exec_paria(t_ms *s, t_cmd *cmds)
{
	if (!cmds || cmds->type != EXEC)
		return (0);
	if (ft_sw_builtins(cmds->argv[0], "export") == 0)
	{
		updating_cmds(s, cmds, s->ast->argv[s->ast->argc - 1]);
		export_cmd(s, cmds->argv);
		return (1);
	}
	else if (ft_sw_builtins(cmds->argv[0], "echo") == 0)
	{
		echo_cmd_test(cmds->argv, s);
		updating_cmds(s, cmds, s->ast->argv[s->ast->argc - 1]);
		return (1);
	}
	else
		return (0);
}

void	updating_cmds(t_ms *s, t_cmd *cmd, char *value)
{
	char	*key;

	key = NULL;
	(void)value;
	(void)cmd;
	if (s->ast->type == 1)
	{
		key = ft_strdup("_");
		export_update(s->export, key, value);
		handle_kv_update(s->env, key, value, 1);
	}
	else if (s->ast->type == 2 || s->ast->type == 4)
	{
		key = ft_strdup("_");
		export_update(s->export, key, value);
		handle_kv_update(s->env, key, value, 1);
	}
}

void	aux_rec_exec(t_ms *s, t_cmd *cmd, int fd_in, int fd_out)
{
	updating_cmds(s, cmd, cmd->argv[cmd->argc - 1]);
	if (ft_exec_builtins_chr(s, cmd->argv))
		s->exit_stat = 0;
	else
		single_exec(s, cmd, fd_in, fd_out);
}

void	exec_from_ast(t_ms *s)
{
	if (!exec_paria(s, s->ast))
		exec_from_ast_recursive(s, s->ast, STDIN_FILENO, STDOUT_FILENO);
}
