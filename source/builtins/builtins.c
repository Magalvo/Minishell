/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:59:25 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/21 13:04:10 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_builtin builtins[] = {
		{"echo", echo_cmd},
		{"cd", cd_cmd},
		{"pwd", pwd_cmd},
		{"export", export_cmd},
		{"unset", unset_cmd},
		{"env", env_cmd},
		{"exit", exit_cmd},
		{NULL, NULL}
};

int	cmd_exec(t_cmd *cmds)
{
	int i;
	
	i = 0;
	if (cmds->cmd_args[0] == NULL)
		return (1);
	while (builtins[i].name != NULL)
	{
		if (ft_strcmp(cmds->cmd_args[0], builtins[i].name) == 0)
			return (builtins[i].func(cmds));
		i++;
	}
	return (1);
}



// int	ft_exec_buitltins(t_cmd *cmds)
// {
// 	if (ft_strcmp(cmds->cmd_args[0], "echo") == 0)
// 		return (echo_cmd(args));
// 	if (ft_strcmp(cmds->cmd_args[0], "cd") == 0)
// 		return (cd_cmd(args));
// 	if (ft_strcmp(cmds->cmd_args[0], "env") == 0)
// 		return (env_cmd(args));
// 	if (ft_strcmp(cmds->cmd_args[0], "pwd") == 0)
// 		return (pwd_cmd(args));
// 	if (ft_strcmp(cmds->cmd_args[0], "export") == 0)
// 		return (export_cmd(args));
// 	if (ft_strcmp(cmds->cmd_args[0], "unset") == 0)
// 		return (unset_cmd(args));
// 	exit_cmd(args);
// 	return (1);
// }






