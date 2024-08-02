/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:59:15 by dde-maga          #+#    #+#             */
/*   Updated: 2024/08/02 10:42:37 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cd_cmd_error(char *msg)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int	change_pwd(t_env *env, t_ms *s)
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

int	cd_cmd_home(t_env *env)
{
	char	*home;
	char	*oldpwd;
	char	*pwd;
	int		result;

	oldpwd = get_env_val(env, "OLDPWD", NULL);
	if (!oldpwd)
		old_pwd(env);
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
}

int	cd_cmd_minus(t_env *env)
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
		free2(old, current_pwd);
		return (0);
	}
	ft_putstr_fd(old, 1);
	write(1, "\n", 1);
	update_key(env, "OLDPWD", current_pwd);
	result = update_key(env, "PWD", old);
	free2(old, current_pwd);
	return (result);
}

int	cd_cmd(t_ms *mini, char **path)
{
	t_env	*env;
	char	*val;
	int		result;

	env = mini->env;
	result = cd_cmd_arg_check(mini);
	if (result != 0)
		return (result);
	result = cd_cmd_handle_home(env, path);
	if (result != 0)
		return (result);
	result = cd_cmd_handle_minus(env, path);
	if (result != 0)
		return (result);
	result = cd_cmd_change_dir(mini, path[1]);
	if (result != 0)
		return (result);
	val = get_env_val(env, "PWD", NULL);
	if (val)
	{
		export_update(env, "OLDPWD", val);
		export_update(mini->export, "OLDPWD", val);
		free(val);
	}
	return (change_pwd(env, mini));
}
