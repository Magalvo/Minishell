/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:59:11 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/22 17:36:23 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* static int	ft_flagged(char *s)
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

int	echo_cmd(t_cmd *cmd)
{
	int		i;
	int		check;
	i = 1;
	check = 0;
	while (cmd->cmd_args[i] != NULL && ft_flagged(cmd->cmd_args[i]) == 1)
	{
		check = 1;
		i++;
	}
	while (cmd->cmd_args[i])
	{
		ft_putstr_fd(cmd->cmd_args[i], 1);
		if(cmd->cmd_args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (check == 0)
		ft_putstr_fd("\n", 1);
	return (0);
} */

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

int	echo_cmd_test(char **cmd)
{
	int		i;
	int		check;
	i = 1;
	check = 0;
	while (cmd[i] != NULL && ft_flagged(cmd[i]) == 1)
	{
		check = 1;
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if(cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (check == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}