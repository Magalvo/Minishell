/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:58:59 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/27 14:34:36 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_key(const char *key)
{
	int i;

	i = 1;
	if(!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	while (key[i] != '\0')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	*extract_key(const char *str, char *delimiter)
{
	size_t key_len = delimiter - str;
	return ft_substr(str, 0, key_len);
}

int	update_key(t_env *env, char *key, char *value)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			free(env->value);
			env->value = value;
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	add_new_node(t_ms *s, char *str)
{
	t_env *new_node = new_env_node(str);
	t_env *env;

	if(!new_node)
		return (0);
	if (!s->env)
		s->env = new_node;
	else
	{
		env = s->env;
		while (env->next)
		{
			env = env->next;
		}	
		env->next = new_node;
		new_node->prev = env;
	}
	return 1;
}

int export_cmd(t_ms *s, char **str)
{
	char	*key;
	char	*value;
	char	*delimiter;

	if (str[1] == NULL) 
		return (printf("\n"), 0);
	delimiter = ft_strchr(str[1], '=');
	if (!delimiter) 
		return (printf("Invalid format for export\n"), 0);
	key = extract_key(str[1], delimiter);
	if (!key)
		return (0);
	if (!is_valid_key(key))
	{
		free(key);
		return(printf("invalid var name\n"),0);
	}
	value = ft_strdup(delimiter + 1);
	if (!update_key(s->env, key, value))
	{
		if (!add_new_node(s, str[1]))
			free_export(key, value);
	}
	free(key);
	return (1);
}



