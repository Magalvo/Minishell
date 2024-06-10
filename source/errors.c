/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:40:06 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/27 12:48:31 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	error_msg(char *str)
{
	if (str)
		perror(str);
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
		if (paths[i])
			free(paths[i]);
		ctd++;
	}
	free(paths);
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
	return(0);
}

int	not_found(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(EXIT_FAILURE);
}