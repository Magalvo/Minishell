/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:58:55 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/27 15:41:11 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd_cmd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, FILENAME_MAX);
	if (pwd != NULL)
		printf("%s\n", pwd);
	else
		perror("pwd");
	return (1);
}
