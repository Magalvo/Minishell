/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:58:55 by dde-maga          #+#    #+#             */
/*   Updated: 2024/07/19 12:12:42 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd_cmd(t_ms *s)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, FILENAME_MAX);
	if (pwd != NULL)
		printf("%s\n", pwd);
	else
	{
		pwd = get_env_val(s->env, "PWD", s);
		printf("%s\n", pwd);
	}
	free(pwd);
	s->exit_stat = 0;
	return (1);
}
