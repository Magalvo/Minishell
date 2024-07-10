/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicarval <dicarval@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:20:10 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/10 16:27:06 by dicarval         ###   ########.fr       */
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
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	free(key);
	return (1);
}

void	wait_till_end(t_ms *s, pid_t pid, t_cmd *cmd)
{
	int	status;

	(void)cmd;
	waitpid(pid, &status, 0);
	if (s->ast->type == 2 && s->exit_stat == 1)
		return ;
/* 	printf("ANTES STATUS: -> %d\n", status);
	printf("EXIT: -> %d\n\n", s->exit_stat); */
	if (WIFEXITED(status))
	{
		if (s->wait == 0)
			s->exit_stat = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		//printf("Entrou no IF");
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
	{
		s->exit_stat /= 256;
	}
	//printf("EXIT: -> %d\n\n", s->exit_stat);
	s->wait += 1;
}
/* 	printf("CMD: -> %d\n", s->ast->type);
	printf("DEPOIS STATUS: -> %d\n", status);
	printf("EXIT: -> %d\n\n", s->exit_stat);
	printf("WAIT ->%d\n", s->wait); */
/* 		printf("CMD: -> %d\n", s->ast->type);
		printf("STATUS: -> %d\n", status);
		printf("EXIT: -> %d\n\n", s->exit_stat); */

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

/* 	printf("STATUS: %d\n", status);
	printf("EXIT: %d\n", s->exit_stat); */
	/* 	if (status == 13)
		s->exit_stat = s->exit_stat; */

/* 		printf("CMD: -> %s\n", cmd->argv[0]);
		printf("STATUS: -> %d\n", status);
		printf("EXIT: -> %d\n\n", s->exit_stat); */
