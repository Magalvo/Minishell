/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:20:10 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/03 21:55:19 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
char	*get_env_expand(char *key)
{
	char	*val;

	if (key[0] == '$')
		key = key + 1;
	val = getenv(key);
	return (val);
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

int	export_cmd_error(t_ms *s, char *msg, char *key)
{
	(void)key;
	s->exit_stat = 1;
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

void	wait_till_end(t_ms *s, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
/* 	if (status == 13)
		s->exit_stat = s->exit_stat; */
	if (WIFEXITED(status))
		s->exit_stat = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		s->exit_stat = 128 + WTERMSIG(status);
	}
	if (s->exit_stat == 131)
		printf("Quit\n");
	if (s->exit_stat == 130)
		printf("\n");
	if (s->exit_stat == 2)
	{
		s->exit_stat = 130;
		printf("\n");
	}
	if (s->exit_stat > 255)
		s->exit_stat /= 256;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}

void	close_fd(int *fd)
{
	if (*fd >= 0)
	{
		close(*fd);
		*fd = -1;
	}
}
