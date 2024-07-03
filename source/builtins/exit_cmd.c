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

void	print_exit(t_ms *s, char *cmds, char *str, int status)
{
	s->exit_stat = status;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmds, STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	exit_minishell(s, NULL);
}

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
			/* if (s->exit_stat > 255)
				s->exit_stat %= 256; */
			exit_minishell(s, "exit\n");
		}
		else
		{
			print_exit(s, cmds[0], ": numeric argument required\n", 2);
		}
	}
	else if (s->ast->argc > 3)
	{
		print_exit(s, cmds[0],  " : Too many arguments\n", 1);
	}
	else
		exit_minishell(s, "exit\n");
}
