/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:20:10 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/09/18 22:52:05 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	old_pwd(t_env *env)
{
	char	*pwd;

	pwd = get_env_val(env, "PWD", NULL);
	if (pwd)
	{
		add_new_node(env, "OLDPWD", pwd);
		free(pwd);
	}
}

int	cd_cmd_arg_check(t_ms *mini)
{
	if (mini->ast->argc >= 3)
	{
		mini->exit_stat = 1;
		return (cd_cmd_error("too many arguments"));
	}
	return (0);
}

int	cd_cmd_handle_home(t_env *env, char **path)
{
	if (!path[1] || (path[1][0] == '~' && path[1][1] == '\0'))
		return (cd_cmd_home(env));
	return (0);
}

int	cd_cmd_handle_minus(t_env *env, char **path)
{
	if (!path[1] || (path[1][0] == '~' && path[1][1] == '\0'))
		return (cd_cmd_home(env));
	return (0);
}

int	cd_cmd_change_dir(t_ms *mini, char *dir)
{
	if (chdir(dir) == -1)
	{
		mini->exit_stat = 1;
		if (access(dir, F_OK) == 0)
			return (cd_cmd_error("Not a directory"));
		return (cd_cmd_error("No such file or directory"));
	}
	return (0);
}
