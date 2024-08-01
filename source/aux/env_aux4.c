/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_aux4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:20:18 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/08/01 12:38:55 by dde-maga         ###   ########.fr       */
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

// todo check line 47, what is DIR ? -dir- prob
// ? something we can use its good to go
int	is_dir(const char *cmd)
{
	DIR	*dir = opendir(cmd);

	if (dir)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

void	swipper_fds(void)
{
	int	fd;

	for (fd = 0; fd < 1024; fd++) {
		close(fd);
	}
}

char	**create_env_array(int ctd_ptr)
{
	char	**env_array;

	env_array = (char **)ft_calloc((ctd_ptr + 1), sizeof(char *));
	if (!env_array)
	{
		ft_putstr_fd("env_arr", 2);
		return (NULL);
	}
	return (env_array);
}
