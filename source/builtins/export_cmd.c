/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:58:59 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/22 19:06:00 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* int	export_cmd(t_ms *s, t_cmd *cmd)
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
				add_env_node();
				printf("exporting...");
				break;
			}
			env = env->next;
		}
		else
			return(error_msg("Export need Args!"), 0);
	}
	return (1);
} */

/*  int	export_cmd(t_ms *s, char **cmds)
{
	char **envp;
	int i = 0;

	envp = s->env_tmp;
	while (*envp)
	{
		if (s->cmd_temp[1] != NULL && (ft_strcount(s->cmd_temp[1], '=') == 1))
		{
			while (ft_isalnum(s->cmd_temp[1][i]) && )
			{
				env->value = cmd->cmd_args[1];
			}
			else if (cmd->cmd_args[1] || env->value == NULL)
			{
				add_env_node();
				printf("exporting...");
				break;
			}
			envp++;
		}
		else
			return(error_msg("Export need Args!"), 0);
	}
	return (1);
} */

