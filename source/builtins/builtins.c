/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:59:25 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/21 17:02:35 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//! Executar Builtins no processo pai a nao ser o printenv; 
// ? Talvez possa ser no filho segundo o Mindmap  D:  :')

int	ft_exec_buitltins(t_minis *mini, t_cmd *cmds)
{
	if (ft_strcmp(cmds->cmd_args[0], "echo") == 0)
		return (echo_cmd(cmds));
	if (ft_strcmp(cmds->cmd_args[0], "cd") == 0)
		return (cd_cmd(mini));
	if (ft_strcmp(cmds->cmd_args[0], "env") == 0)
		return (env_cmd(mini));
	if (ft_strcmp(cmds->cmd_args[0], "pwd") == 0)
		return (pwd_cmd(mini));
	if (ft_strcmp(cmds->cmd_args[0], "export") == 0)
		return (export_cmd(mini));
	if (ft_strcmp(cmds->cmd_args[0], "unset") == 0)
		return (unset_cmd(mini));
	exit_cmd(mini);
	return (1);
}






