/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:59:04 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/21 16:59:27 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	aux_all(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while(str[i])
	{
		if(!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void exit_cmd(t_ms *s, char **cmds)
{
    if (cmds[1] && !cmds[2])
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
    else if (cmds[2] && cmds[2][0])
    {
        s->exit_stat = 1;
        ft_putstr_fd(cmds[0], STDERR_FILENO);
        ft_putstr_fd(" `: too many arguments\n", STDERR_FILENO);
        exit_minishell(s, "exit\n");
    }
    else
        exit_minishell(s, "exit\n"); 
}
