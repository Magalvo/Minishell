/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_aux3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:20:45 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/09/18 15:29:25 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*key_dup(char *env_var, size_t key_len)
{
	return (ft_strndup(env_var, key_len));
}

int	setting_value(t_env *node, char *delimiter)
{
	int	num;

	if (!ft_strncmp("SHLVL", node->key, 5))
	{
		num = ft_atoi(delimiter + 1);
		node->value = ft_itoa(num + 1);
	}
	else
		node->value = ft_strdup(delimiter + 1);
	if (!node->value)
	{
		free(node->key);
		free(node);
		return (0);
	}
	return (1);
}

void	free_node(t_env *node)
{
	if (node)
	{
		free(node->key);
		free(node->value);
		free(node);
	}
}

void	dup_and_close(t_ms *s, int *fd_this, int *fd_aux, int standard)
{
	if (dup2(*fd_this, standard) < 0)
	{
		s->exit_stat = 1;
		close_fd(fd_this);
		if (*fd_aux != STDIN_FILENO && *fd_aux != STDOUT_FILENO)
			close_fd(fd_aux);
		exit_minishell(s, NULL);
	}
	close_fd(fd_this);
}

void	free_env_array(char **env_array)
{
	int	i;

	i = 0;
	if (!env_array)
		return ;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}
