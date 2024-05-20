/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:04:53 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/20 15:04:58 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

//! exec prototype, (MIGHT GO KABUM!)

int	cmd_exec(char **args)
{
	int i;

	i = 0;
	if (args[0] == NULL)
		return (1);
	while (i < builtin_num())
	{
		if (ft_strncmp(args[0], built))
	}
}