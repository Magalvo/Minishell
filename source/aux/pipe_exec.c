/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:42:53 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/10 16:56:33 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// TODO Function has more than 25 lines
void	exec_one(t_ms *s, char **argv)
{
	char	*path;
	char	*cmd_name;

	if ((argv[0] && argv[0][0] == '.' && argv[0][1] == '/' && argv[0][2]) || \
		(argv[0] && argv[0][0] == '/' && argv[0][1]))
	{
		if (access(argv[0], F_OK) != 0)
		{
			not_found(argv[0], 127, s);
			s->exit_stat = 127;
			return ;
		}
		else if (access(argv[0], X_OK) != 0)
		{
			not_found(argv[0], 126, s);
			s->exit_stat = 126;
			return ;
		}
		if (!execve(argv[0], argv, s->env_tmp))
			exit(EXIT_FAILURE);
	}
	if (argv && argv[0] != NULL)
	{
		path = cmd_path(s->paths, argv[0], s);
		if (!path)
		{
			not_found(argv[0], 127, s);
			s->exit_stat = 127;
			return ;
		}
		cmd_name = ft_strchr(argv[0], '/');
		if (cmd_name)
			argv[0] = ++cmd_name;
		execve(path, argv, s->env_tmp);
		free(path);
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
		handle_kv_update(s->env, key, value, 1);
	}
	else if (s->ast->type == 2 || s->ast->type == 4)
	{
		key = ft_strdup("_");
		export_update(s->export, key, value);
		handle_kv_update(s->env, key, value, 1);
	}
}


int	builtins_parent(t_ms *s, char **cmds, int fd_in, int fd_out)
{
	(void)fd_in;
	(void)fd_out;
	if (ft_sw_builtins(cmds[0], "cd") == 0)
		return (cd_cmd(s, cmds), 1);
	else if (ft_sw_builtins(cmds[0], "env") == 0)
		return (env_cmd(s, cmds));
	else if (ft_sw_builtins(cmds[0], "pwd") == 0)
		return (pwd_cmd(s));
	else if (ft_sw_builtins(cmds[0], "export") == 0)
		return (export_cmd(s, cmds), 1);
	else if (ft_sw_builtins(cmds[0], "unset") == 0)
		return (unset_cmd(s, cmds));
	else if (ft_sw_builtins(cmds[0], "exit") == 0)
		return (exit_cmd(s, cmds), 1);
	else if (ft_sw_builtins(cmds[0], "bnf") == 0)
		return (s->bnf = true, ft_putstr_fd("bnf ON\n", 1), 1);
	else
		return (0);
}

void	aux_rec_exec(t_ms *s, t_cmd *cmd, int fd_in, int fd_out)
{
	if(ft_strlen(cmd->argv[0]) == 0)
	{
		if (cmd->argv[0][0] == '\x11')
			cmd = cmd->cmd;
		if(ft_isspace(cmd->argv[0][0] || cmd->argv[0][0] == '\0'))
			not_found(cmd->argv[0], 127, s);
		
		return ;
	}
	if (s->ast && s->ast->argc > 0)
		updating_cmds(s, cmd, cmd->argv[cmd->argc - 1]);
	if (!builtins_parent(s, cmd->argv, fd_in, fd_out))
		single_exec(s, cmd, fd_in, fd_out);
}

void	exec_from_ast(t_ms *s)
{
	char	**original;

	if (!s->ast)
		return ;
	original = s->ast->argv;
	if (s->ast->type == EXEC && s->ast->argv[0][0] == '\0')
	{
		while (*s->ast->argv && **s->ast->argv == '\0')
			s->ast->argv++;
	}
	if (!ft_exec_paria(s, s->ast))
		exec_from_ast_recursive(s, s->ast, STDIN_FILENO, STDOUT_FILENO);
	if (s->ast->type == EXEC)
		s->ast->argv = original;
	s->wait = 0;
}
