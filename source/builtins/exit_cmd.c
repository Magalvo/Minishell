/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:59:04 by dde-maga          #+#    #+#             */
/*   Updated: 2024/06/29 01:34:34 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	aux_all(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exit_cmd(t_ms *s, char **cmds)
{
	if (s->ast->argc == 2)
	{
		if (aux_all(cmds[1]))
		{
			s->exit_stat = ft_atoi(cmds[1]);
			if (s->exit_stat > 255)
				s->exit_stat %= 256;
		}
		else
		{
			s->exit_stat = 2;
			ft_putstr_fd(cmds[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			exit_minishell(s, "exit\n");
		}
	}
	else if (s->ast->argc > 2) //&& cmds[2][0]
	{
		s->exit_stat = 1;
		ft_putstr_fd(cmds[0], STDERR_FILENO);
		ft_putstr_fd(" `: too many arguments\n", STDERR_FILENO);
		exit_minishell(s, "exit\n");
	}
	else
		exit_minishell(s, "exit\n");
}
