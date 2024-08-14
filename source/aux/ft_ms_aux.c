/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:21:13 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/08/14 10:09:22 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_getrnd_str(void)
{
	int		fd;
	char	res[STR_SIZE + 1];
	char	buf[1];
	int		i;

	i = 0;
	fd = open("/dev/urandom", O_RDONLY);
	if (!fd)
		return (NULL);
	while (i < STR_SIZE)
	{
		read(fd, buf, 1);
		if (ft_isalnum(buf[0]))
		{
			res[i] = buf[0];
			i++;
		}
	}
	close(fd);
	res[STR_SIZE] = '\0';
	return (ft_strdup(res));
}

// todo comments
char	*ft_get_empty(void)
{
	char	*empty;

	empty = ft_calloc(1, 2);
	empty[0] = EMPTY;
	empty[1] = '\0';
	return (empty);
}

// if $$ found replace with result from:	char pid_res = ft_getpid();
char	*ft_getpid(void)
{
	char		*pid_res;
	int			fd;
	char		**stat;

	fd = open("/proc/self/stat", O_RDONLY);
	if (!fd)
		return (close_fd(&fd), NULL);
	pid_res = get_next_line(fd);
	close_fd(&fd);
	if (!pid_res)
		return (NULL);
	stat = ft_split(pid_res, ' ');
	free(pid_res);
	if (!stat)
		return (NULL);
	pid_res = ft_strdup(stat[0]);
	ft_free_dptr(&stat);
	if (!pid_res)
		return (NULL);
	return (pid_res);
}

void	init_aux(t_env **head, t_env **tail, t_env *new_node)
{
	if (*tail)
	{
		(*tail)->next = new_node;
		new_node->prev = *tail;
		*tail = new_node;
	}
	else
	{
		*head = new_node;
		*tail = new_node;
	}
}
// for historical reasons this monstrosity shall remain here.
// If it's stupid and it works is not stupid, then there's this function...
/*
char	*get_pid(t_ms *s)
{
	pid_t		pid;
	char		*pid_res;
	int			fd[2];
	char		**stat;
	static char	*command[3] = {"/bin/cat", "/proc/self/stat", NULL};
	int			stdin_copy;

	pipe(fd);
	pid = fork();
	if (pid == -1)
		error_msg("error on pid");
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execve(command[0], command, s->env_tmp);
	}
	else
	{
		close(fd[1]);
		stdin_copy = dup(STDIN_FILENO); // Save the original STDIN
		dup2(fd[0], STDIN_FILENO);
		pid_res = get_next_line(fd[0]);
		dup2(stdin_copy, STDIN_FILENO); // Restore the original STDIN
		close(stdin_copy); // Close the copy
		close(fd[0]);
		wait(0);
		stat = ft_split(pid_res, ' ');
		pid_res = ft_strdup(stat[3]);
		free(stat);
		return (pid_res);
	}
	return (NULL);
}*/
