/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:58:55 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/21 12:51:11 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd_cmd(t_cmd *cmd)
{
	(void)cmd;
/* 	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf ("%s\n", cwd);
	else
		perror("pwd"); */
	return (1);
}