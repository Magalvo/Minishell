/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:42:53 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/09/18 22:37:16 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*path_constructor(const char *path, const char *cmd, int slashi)
{
	char	*new_path;
	char	*temp;

	new_path = NULL;
	if (slashi)
	{
		temp = ft_strjoin(path, "/");
		if (!temp)
			return (NULL);
		new_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!new_path)
			return (NULL);
	}
	if (ft_strncmp(cmd, "./", 2) != 0 && ft_strcmp(path, "/usr/bin") != 0)
	{
		free(new_path);
		return (NULL);
	}
	else if (new_path && access(new_path, X_OK) == 0)
		return (new_path);
	free(new_path);
	return (NULL);
}

void	exec_one(t_ms *s, char **argv)
{
	if ((argv[0] && argv[0][0] == '.' && argv[0][1] == '/' && argv[0][2]) ||
		(argv[0] && argv[0][0] == '/' && argv[0][1]))
	{
		exec_dir_path(s, argv);
		return ;
	}
	else if (argv && argv[0] != NULL)
	{
		exec_command_path(s, argv);
	}
}

int	ft_exec_paria(t_ms *s, t_cmd *cmds)
{
	if (!cmds || cmds->type != EXEC)
		return (0);
	if (!(*s->ast->argv))
		return (1);
	if (ft_sw_builtins(cmds->argv[0], "export") == 0)
	{
		updating_cmds(s, cmds, s->ast->argv[s->ast->argc - 1]);
		export_cmd(s, cmds->argv);
		return (1);
	}
	else if (ft_sw_builtins(cmds->argv[0], "echo") == 0)
	{
		echo_cmd_test(cmds->argv, s, STDIN_FILENO, STDOUT_FILENO);
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
	if (!value)
		value = NULL;
	(void)cmd;
	if (s->ast->type == 1)
	{
		key = ft_strdup("_");
		export_update(s->export, key, value);
		handle_kv_update(s->env, key, value, 0);
	}
	else if (s->ast->type == 2 || s->ast->type == 4)
	{
		key = ft_strdup("_");
		export_update(s->export, key, value);
		handle_kv_update(s->env, key, value, 0);
	}
	if (key)
		free(key);
}

int	builtins_parent(t_ms *s, char **cmds, int fd_in, int fd_out)
{
	(void)fd_in;
	(void)fd_out;
	if (ft_sw_builtins(cmds[0], "cd") == 0)
		return (cd_cmd(s, cmds));
	else if (ft_sw_builtins(cmds[0], "env") == 0)
		return (env_cmd(s, cmds));
	else if (ft_sw_builtins(cmds[0], "pwd") == 0)
		return (pwd_cmd(s));
	else if (ft_sw_builtins(cmds[0], "export") == 0)
		return (export_cmd(s, cmds), 1);
	else if (ft_sw_builtins(cmds[0], "unset") == 0)
		return (unset_cmd(s, cmds));
	else if (ft_sw_builtins(cmds[0], "exit") == 0 && s->ast->type != 3)
	{
		close_fd(&fd_in);
		close_fd(&fd_out);
		return (exit_cmd(s, cmds), 1);
	}
	else if (ft_sw_builtins(cmds[0], "bnf") == 0)
		return (s->bnf = true, ft_putstr_fd("bnf ON\n", 1), 1);
	else
		return (0);
}
