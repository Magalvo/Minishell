/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:58:59 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/22 16:15:16 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	export_cmd(t_ms *s, t_cmd *cmd)
{
	t_env	*env;
	
	env = s->env;
	while (env)
	{
		if (cmd->cmd_args[1] != NULL)
		{
			if (env->key == cmd->cmd_args[0] && cmd->cmd_args[1])
				env->value = cmd->cmd_args[1];
			else if (cmd->cmd_args[1] || env->value == NULL)
			{
				//*add_env_node();
				printf("exporting...");
				break;
			}
			env = env->next;
		}
		else
			return(error_msg("Export need Args!"));
	}
	return (1);
}