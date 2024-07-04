/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:59:04 by dde-maga          #+#    #+#             */
/*   Updated: 2024/07/04 18:12:17 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_exit(t_ms *s, char *cmds, char *str, int status)
{
	s->exit_stat = status;
	ft_putstr_fd("exit\n", 1);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmds, STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	//exit_minishell(s, NULL);
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
	else if (s->ast->argc >= 3)
	{
		// TODO should not exit, if following bash
		//SOLVED
		print_exit(s, cmds[0],  " : too many arguments\n", 1);
	}
	else
		exit_minishell(s, "exit\n");
}
