/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:59:11 by dde-maga          #+#    #+#             */
/*   Updated: 2024/06/27 15:03:44 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_flagged(char *s)
{
	//int	i;
	//i = 0;
	if (s[0] != '-')
		return (0);
	if (s[0] == '-' && s[1] == 'n' && s[2] == '\0')
		return (1);
	else
		return (0);
	/* i++;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (0); */
}

int echo_cmd_test(char **cmd, t_ms *s) {
    int i;
    int check;

    (void)s;
    i = 1;
    check = 0;

    if (!cmd || !cmd[0]) {
        printf("Error: cmd is null or cmd[0] is null\n");
        return 0;
    }

    printf("Debug: Initial cmd contents:\n");
    for (int j = 0; cmd[j] != NULL; j++) {
        printf("cmd[%d]: %s\n", j, cmd[j]);
    }

    while (cmd[i] != NULL && ft_flagged(cmd[i]) == 1) {
        check = 1;
        i++;
    }

    printf("Debug: After checking flags, starting at cmd[%d]\n", i);

    while (cmd[i]) {
        printf("Debug: Processing cmd[%d]: %s\n", i, cmd[i]); // Add debug for each element
        ft_putstr_fd(cmd[i], 1);
        if (cmd[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }

    if (check == 0)
        ft_putstr_fd("\n", 1);

    printf("Debug: Finished echo_cmd_test\n");
    return 1;
}


