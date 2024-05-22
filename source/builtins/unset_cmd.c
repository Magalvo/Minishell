/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:58:50 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/22 16:21:37 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	unset_cmd(t_ms *s, t_cmd *cmd)
{
	t_env	*env;
	
	env = s->env;
	while (env)
	{
		if (cmd->cmd_args[1] != NULL)
		{
			if (cmd->cmd_args[1] == env->key)
				env.key = cmd->cmd_args[1];
			env = env->next;
		}
		else
			return(error_msg("Unset need Args!"));
	}
	return (1);
}
