/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:20:10 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/30 18:34:04 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// todo remove !!!!!s or not
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
	if (key[0] == '-')
	{
		s->exit_stat = 2;
		msg = "usage: export [-nf] [name[=value] ...] or export -p";
	}
	else
		s->exit_stat = 1;
	ft_putstr_fd("minishell: export: `", 2);
	if (s->exit_stat == 1)
	{
		ft_putstr_fd(key, 2);
		ft_putstr_fd("'", 2);
	}
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

void	wait_till_end(t_ms *s, pid_t pid, t_cmd *cmd)
{
	int	status;

	(void)cmd;
	waitpid(pid, &status, 0);
	if (s->ast->type == 2 && s->exit_stat == 1)
		return ;
	if (WIFEXITED(status))
	{
		if (s->wait == 0)
			s->exit_stat = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		if (s->wait == 0)
			s->exit_stat = 128 + WTERMSIG(status);
		if (s->exit_stat == 131 && s->wait == 0)
			printf("Quit\n");
		if (s->exit_stat == 130 && s->wait == 0)
			printf("\n");
		if (s->exit_stat == 141 && s->wait == 0)
			s->exit_stat = 0;
	}
	if (s->exit_stat > 255 && s->wait == 0)
		s->exit_stat /= 256;
	s->wait += 1;
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
