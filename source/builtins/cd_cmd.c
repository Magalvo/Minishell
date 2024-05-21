/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:59:15 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/21 12:49:39 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cd_cmd(t_cmd *cmd)
{
	(void)cmd;
/* 	if (cmd == NULL)
		ft_sprintf(2,"cd need arguments");
	else
	{
		if (chdir(cmd != 0))
			perror ("cd");
	} */
	return (1);
}