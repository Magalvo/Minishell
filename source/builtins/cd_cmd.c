/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:59:15 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/27 15:55:50 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	change_pwd(t_env *env)
{
	char	*cmd;
	int		result;
	
	cmd = getcwd(NULL, 0);
	if (!cmd)
		return(ft_putstr_fd("Failed to change Dir\n", 2), 0);
	result = update_key(env, "PWD", cmd);
	free(cmd);
	return (result);
}

static int	cd_cmd_home(t_env *env)
{
	char	*home;
	
	update_key(env, "OLDPWD", get_env_val(env, "PWD"));
	home = get_env_val(env,"HOME");
	if (!home)
		return (ft_putstr_fd("Err on ENV\n", 2), 0);
	if (chdir(home) == -1)
		return (ft_putstr_fd("Failed to change directory\n", 2), 0);
	return (update_key(env, "PWD", home), 1);
}


static int	cd_cmd_error(char *msg)
{
	ft_putstr_fd("minishell: cd: `", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("'No such file or Directory\n", 2);
	return (1);
}

int	cd_cmd(t_ms *mini, char **path)
{
	t_env *env;

	env=mini->env;
	if(!path[1] || (path[1][0] == '~' && path[1][1] == '\0'))
		return (cd_cmd_home(env));
	if(chdir(path[1]) == -1)
		return (cd_cmd_error(path[1]));
	update_key(env, "OLDPWD=", get_env_val(env, "PWD="));
	return(change_pwd(env));
}