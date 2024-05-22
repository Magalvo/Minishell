/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:59:07 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/22 15:49:30 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//!===========================================
//? O sinal de = faz parte da key ou do value?
//!===========================================

int	env_cmd(t_ms *s)
{
	t_env	*env;

	env = s->env;
	while(env)
	{
		if (env->value != NULL)
			printf("%s=%s\n", env->key, env->value)
		env = env->next;
	}	
	return (1);
}
