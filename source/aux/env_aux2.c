/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_aux2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:20:37 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/30 17:41:36 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*env_paths(t_ms *ms, char **envp)
{
	char	**paths;
	char	*slash;
	int		i;
	int		found;

	i = -1;
	found = 0;
	slash = NULL;
	paths = NULL;
	if (ms->paths)
		free_all_paths(ms->paths);
	while (envp[++i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			found = 1;
			paths = ft_split(envp[i] + 5, ':');
			break ;
		}
	}
	if (!found || !paths)
		paths = ft_split(MIN_PATH, ':');
	add_slash(slash, paths);
	ms->paths = paths;
	return (NULL);
}

char	*get_path_value(t_ms *s)
{
	int		i;
	int		total_len;
	char	*result;

	i = 0;
	total_len = 0;
	while (s->paths && s->paths[i])
	{
		total_len += ft_strlen(s->paths[i]);
		if (s->paths[i + 1] != NULL)
			total_len++;
		i++;
	}
	result = ft_calloc(total_len + 1, sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (s->paths && s->paths[i])
	{
		ft_strcat(result, s->paths[i]);
		if (s->paths[i + 1] != NULL)
			ft_strcat(result, ":");
		i++;
	}
	return (result);
}

char	*get_other_env_val(t_env *env, char *key)
{
	t_env	*tmp_env;
	char	*value;
	char	*result;

	tmp_env = env;
	while (env)
	{
		if(ft_strncmp(env->key, key, ft_strlen(key)) == 0 && \
			ft_strlen(env->key) == ft_strlen(key))
		{
			value = env->value;
			result = ft_strdup(value);
			return (result);
		}
		env = env->next;
	}
	env = tmp_env;
	return (NULL);
}

char	*get_env_val(t_env *env, char *key, t_ms *s)
{
	if (ft_strncmp(key, "PATH", 4) == 0)
		return get_path_value(s);
	else
		return get_other_env_val(env, key);
}

char	**env_convert(t_env *env)
{
	int		i;
	int		ctd;
	char	**env_array;
	t_env	*current;

	ctd = 0;
	current = env;
	i = 0;
	while (current)
	{
		ctd++;
		current = current->next;
	}
	env_array = create_env_array(ctd);
	current = env;
	i = 0;
	while (current && i < ctd)
	{
		env_array[i++] = join_key_value(current->key, current->value);
		if (!env_array[i - 1])
			return (free_env_array(env_array), NULL);
		current = current->next;
	}
	env_array[i] = NULL;
	return (env_array);
}


/* char	*get_env_val(t_env *env, char *key, t_ms *s)
{
	int		i;
	int		total_len;
	char	*value;
	char	*result;
	t_env	*tmp_env;

	i = 0;
	if (ft_strncmp(key, "PATH", 4) == 0)
	{
		total_len = 0;
		while (s->paths && s->paths[i])
		{
			total_len += ft_strlen(s->paths[i]);
			if (s->paths[i + 1] != NULL)
				total_len++;
			i++;
		}
		result = ft_calloc(total_len + 1, sizeof(char *));
		if (!result)
			return (NULL);
		i = 0;
		while (s->paths && s->paths[i])
		{
			ft_strcat(result, s->paths[i]);
			if (s->paths[i + 1] != NULL)
				ft_strcat(result, ":");
			i++;
		}
		return (result);
	}
	else
	{
		tmp_env = env;
		while (env)
		{
			if (ft_strncmp(env->key, key, ft_strlen(key)) == 0 && \
				ft_strlen(env->key) == ft_strlen(key))
			{
				value = env->value;
				result = ft_strdup(value);
				return (result);
			}
			env = env->next;
		}
		env = tmp_env;
	}
	return (NULL);
} */
