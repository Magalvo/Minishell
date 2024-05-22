/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:59:07 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/21 17:03:15 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env_cmd(t_ms *mini)
{
	(void)mini;
	int i;

	i = 0;
	while(mini->env && mini->env[i] != NULL)
	{
		if (ft_strchr(mini->env[i], '='))
			printf("%s", mini->env[i]);
		i++;
	}
	return (1);
}
