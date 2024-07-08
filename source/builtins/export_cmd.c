/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:58:59 by dde-maga          #+#    #+#             */
/*   Updated: 2024/07/08 19:14:40 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_key(char *key)
{
	int	i;

	i = 1;
	if (!ft_isalpha(key[0]) && key[0] != '_')
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
	size_t	key_len;

	key_len = delimiter - str;
	return (ft_substr(str, 0, key_len));
}

//!! AQUI
int	update_key(t_env *env, char *key, char *value)
{
	char	*value_tmp;
	t_env	*env_hold;

	env_hold = env;
	while (env)
	{
		if (ft_sw_builtins(env->key, key) == 0)
		{
			if (value)
			{
				if (env->value != NULL && ft_strcmp(value, env->value) == 0)
					return (1);
				value_tmp = ft_strdup(value);
				if (!value_tmp)
					return (0);
				free(env->value);
				env->value = value_tmp;
			}
			return (1);
		}
		env = env->next;
	}
	env = env_hold;
	return (0);
}

int	add_new_node(t_env *env, char *key, char *value)
{
	t_env	*env_cpy;
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		error_msg("malloc (new env)");
	new_node->key = ft_strdup(key);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->prev = NULL;
	new_node->next = NULL;
	if (!env)
		env = new_node;
	else
	{
		env_cpy = env;
		while (env_cpy->next)
			env_cpy = env_cpy->next;
		env_cpy->next = new_node;
		new_node->prev = env_cpy;
	}
	return (0);
}

int	export_cmd(t_ms *s, char **str)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	if (str[1] == NULL)
		return ((sort_env_list(&s->export)), print_export(s->export));
	while (str[++i])
	{
		key = NULL;
		value = NULL;
		key = get_key_from_str(str[i]);
		if (!key || !is_valid_key(key))
			export_cmd_error(s, ": not a valid identifier", key);
		else
		{
			value = get_value_from_str(str[i]);
			export_update(s->export, key, value);
			handle_kv_update(s->env, key, value, 1);
			env_arr_update(s, NULL);
			env_paths(s, s->env_tmp);
		}
	}
	return (0);
}
