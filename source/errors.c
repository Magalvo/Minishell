/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:40:06 by dde-maga          #+#    #+#             */
/*   Updated: 2024/08/05 14:40:11 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	error_msg(char *str)
{
	if (str)
		perror(str);
	else
		perror("ERROR :(");
	exit(EXIT_FAILURE);
}

int	free_export(char *key, char *value)
{
	free(key);
	free(value);
	return (error_msg("failed to create new node"), 0);
}

void	free_paths(char **paths, int i)
{
	int	ctd;

	ctd = 0;
	if (!paths)
		return ;
	while (ctd < i)
	{
		if (paths[ctd])
			free(paths[ctd]);
		ctd++;
	}
	free(paths);
}

void	free_all_paths(char **paths)
{
	int	i;

	i = 0;
	if (!paths)
		return ;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
	paths = NULL;
}

int	free_export_p(t_env *env_copy, t_env *new_node)
{
	while (env_copy)
	{
		new_node = env_copy;
		env_copy = env_copy->next;
		free(new_node->key);
		free(new_node->value);
		free(new_node);
	}
	return (0);
}
