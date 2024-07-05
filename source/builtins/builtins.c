/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:59:25 by dde-maga          #+#    #+#             */
/*   Updated: 2024/07/03 17:20:05 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	add_slash(char *slash, char **paths)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (paths[i])
	{
		len = ft_strlen(paths[i]);
		if (paths[i][len - 1] != '/')
		{
			slash = ft_strjoin(paths[i], "/");
			if (!slash)
				return (free_paths(paths, i), 0);
			free(paths[i]);
			paths[i] = slash;
		}
		i++;
	}
	return (1);
}

//! Executar Builtins no processo pai a nao ser o printenv;
// ? Talvez possa ser no filho segundo o Mindmap  D:  :')

int	ft_sw_builtins(const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len != s2_len)
	{
		return (ft_abs(s1_len - s2_len));
	}
	if (ft_ismax(s1_len, s2_len))
		return (ft_strncmp(s1, s2, s2_len));
	else
		return (ft_strncmp(s1, s2, s1_len));
}

void	toggle_bnf(t_ms *s)
{
	if (s->bnf == true)
	{
		s->bnf = false;
		ft_putstr_fd("bnf: OFF\n", 1);
	}
	else if (s->bnf == false)
	{
		s->bnf = true;
		ft_putstr_fd("bnf: ON\n", 1);
	}
}

int	ft_exec_builtins_chr(t_ms *s, char **cmds, int fd_in, int fd_out)
{
/* 	if (cmds == NULL || cmds[0] == NULL)
		return (1); */
	if (ft_sw_builtins(cmds[0], "echo") == 0)
		return (echo_cmd_test(cmds, s, fd_in, fd_out), 1);
	else if (ft_sw_builtins(cmds[0], "cd") == 0)
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

/* int	ft_exec_buitltins(t_ms *s, char **cmds)
{
	int	i;
	int	len;

int	add_slash(char *slash, char **paths)
{
	len = 0;
	i = 0;
	while (paths[i])
	{
		len = ft_strlen(paths[i]);
		if (paths[i][len - 1] != '/')
		{
			slash = ft_strjoin(paths[i], "/");
			if (!slash)
				return (free_paths(paths, i), 0);
			free(paths[i]);
			paths[i] = slash;
		}
		i++;
	}
	return (1);
}
	if (ft_strcmp(cmds->cmd_args[0], "echo") == 0)
		return (echo_cmd(cmds));
	if (ft_strcmp(cmds->cmd_args[0], "cd") == 0)
		return (cd_cmd(s));
	if (ft_strcmp(cmds->cmd_args[0], "env") == 0)
		return (env_cmd(s));
	if (ft_strcmp(cmds->cmd_args[0], "pwd") == 0)
		return (pwd_cmd(s));
	if (ft_strcmp(cmds->cmd_args[0], "export") == 0)
		return (export_cmd(s, cmds));
	if (ft_strcmp(cmds->cmd_args[0], "unset") == 0)
		return (unset_cmd(s, cmds));
	if (ft_strcmp(cmds->cmd_args[0], "exit") == 0)
		return (exit_cmd(s));
	return (1);
} */
