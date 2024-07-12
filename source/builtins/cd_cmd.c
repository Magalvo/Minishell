/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:59:15 by dde-maga          #+#    #+#             */
/*   Updated: 2024/07/13 00:03:11 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	cd_cmd_error(char *msg)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

static int	change_pwd(t_env *env, t_ms *s)
{
	char	*cmd;
	int		result;

	cmd = NULL;
	cmd = getcwd(cmd, FILENAME_MAX);
	if (!cmd)
	{
		s->exit_stat = 1;
		return (ft_putstr_fd("Failed to change Dir\n", 2), 1);
	}
	result = update_key(env, "PWD", cmd);
	free(cmd);
	return (result);
}

// TODO Function has more than 25 lines
static int	cd_cmd_home(t_env *env)
{
	char	*home;
	char	*oldpwd;
	char	*pwd;
	int		result;

	oldpwd = get_env_val(env, "OLDPWD", NULL);
	if (!oldpwd)
	{
		pwd = get_env_val(env, "PWD", NULL);
		if (pwd)
		{
			add_new_node(env, "OLDPWD", pwd);
			free(pwd);
		}
	}
	else
		free(oldpwd);
	pwd = get_env_val(env, "PWD", NULL);
	if (pwd)
	{
		update_key(env, "OLDPWD", pwd);
		free(pwd);
	}
	home = get_env_val(env, "HOME", NULL);
	if (!home)
		return (ft_putstr_fd("Err on env\n", 2), 1);
	if (chdir(home) == -1)
		return (free(home), ft_putstr_fd("No such file or directory\n", 2), 1);
	result = update_key(env, "PWD", home);
	return (free(home), result);
	/* if (!get_env_val(env, "OLDPWD", NULL))
		add_new_node(env, "OLDPWD", get_env_val(env, "PWD", NULL));
	update_key(env, "OLDPWD", get_env_val(env, "PWD", NULL));
	home = get_env_val(env, "HOME", NULL);
	if (!home)
		return (ft_putstr_fd("Err on ENV\n", 2), 1);
	if (chdir(home) == -1)
		return (ft_putstr_fd("No such file or directory\n", 2), 1);
	return (update_key(env, "PWD", home), 1); */
}

static int	cd_cmd_minus(t_env *env)
{
	char	*old;
	char	*current_pwd;
	int		result;

	current_pwd = get_env_val(env, "PWD", NULL);
	old = get_env_val(env, "OLDPWD", NULL);
	if (!old)
		return (cd_cmd_error("OLDPWD not set"), 1);
	if (chdir(old) == -1)
	{
		ft_putstr_fd("Failed to change directory\n", 2);
		free(old);
		free(current_pwd);
		return (0);
	}
	ft_putstr_fd(old, 1);
	write(1, "\n", 1);
	update_key(env, "OLDPWD", current_pwd);
	result = update_key(env, "PWD", old);
	free(old);
	free(current_pwd);
	return (result);
}

// TODO Function has more than 25 lines
int	cd_cmd(t_ms *mini, char **path)
{
	t_env	*env;
	char	*val;

	env = mini->env;
	if (mini->ast->argc >= 3)
	{
		mini->exit_stat = 1;
		return (cd_cmd_error("too many arguments"));
	}
	if (!path[1] || (path[1][0] == '~' && path[1][1] == '\0'))
		return (cd_cmd_home(env));
	if (path[1][0] == '-' && path[1][1] == '\0')
		return (cd_cmd_minus(env));
	if (chdir(path[1]) == -1)
	{
		mini->exit_stat = 1;
		if (access(path[1], F_OK) == 0)
			return (cd_cmd_error("Not a directory"));
		return (cd_cmd_error("No such file or directory"));
	}
	val = get_env_val(env, "PWD", NULL);
	if (val)
	{
		export_update(env, "OLDPWD", val);
		export_update(mini->export, "OLDPWD", val);
		free(val);
	}
	return (change_pwd(env, mini));
}
