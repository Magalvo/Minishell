/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_aux4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:20:18 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/06/27 13:08:02 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env_pos(t_env *env, char *value)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, value) == 0)
			return (i);
		i++;
		tmp = tmp->next;
	}
	return (0);
}

void	env_arr_update(t_ms *s, char *str)
{
	(void)str;

	if (s->paths)
	{
		free_all_paths(s->paths);
		s->paths = NULL;
	}
	free_env_array(s->env_tmp);
	s->env_tmp = env_convert(s->env);
}
