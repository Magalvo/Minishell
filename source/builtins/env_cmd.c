/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:59:07 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/21 12:48:22 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env_cmd(t_cmd *cmd)
{
	(void)cmd;
	/* extern char **__environ;
	int i = 0;

	while(cmd != NULL)
	{
		printf("%s", __environ[i]);
		i++;	
	} */
	return (1);
}