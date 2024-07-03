/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:59:11 by dde-maga          #+#    #+#             */
/*   Updated: 2024/06/29 01:12:35 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_flagged(char *s)
{
	int i;
	i = 0;
	if (s[0] != '-')
		return (0);
	i++;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo_cmd_test(char **cmd, t_ms *s, int fd_in, int fd_out)
{
	int	i;
	int	check;

	(void)s;
	(void)fd_in;
	(void)fd_out;
	i = 1;
	check = 0;
	while (cmd[i] != NULL && ft_flagged(cmd[i]) == 1)
	{
		check = 1;
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], fd_out);
		if (cmd[i + 1])
			ft_putstr_fd(" ", fd_out);
		i++;
	}
	if (check == 0)
		ft_putstr_fd("\n", fd_out);
	s->exit_stat = 0;
	return (1);
}
