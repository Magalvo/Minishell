/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:58:59 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/27 15:10:09 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_key(const char *key)
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

int	update_key(t_env *env, char *key, char *value)
{
	while (env)
	{
		if (ft_sw_builtins(env->key, key) == 0)
		{
			if (value)
			{
				free(env->value);
				env->value = ft_strdup(value);
			}
			return (1);
		}
		env = env->next;
	}
	return (0);
}

/* int	add_new_node(t_ms *s, char *key, char *value)
{
	t_env	*env;
	char	*key;
	char	*value;
	t_env	*env_cpy;

	t_env *new_node; //= new_env_node(key,value);
	new_node = (t_env *)malloc(sizeof(t_env));
	if(!new_node)
		error_msg("malloc (new env)");
	new_node->key = ft_strdup(key);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->prev = NULL;
	new_node->next = NULL;
	if (!s->env)
		s->env = new_node;
	else
	{
		env = s->env;
		while (env->next)
			env = env->next;
		env->next = new_node;
		new_node->prev = env;
	}
	return (1);
} */
/* int export_cmd(t_ms *s, char **str)
{
	if (str[1] == NULL)
	{
		sort_env_list(&s->export);
		return (print_export(s->export));
	}
	key = get_key_from_str(str[1]);
	value = get_value_from_str(str[1]);
	if(!key)
		return (0);
	export_update(s, key, value);
	handle_kv_update(s, key, value);
	return (1);
} */
int	add_new_node(t_env *env, char *key, char *value)
{
	t_env *new_node; //= new_env_node(key,value);
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
	return (1);
}

int	export_cmd(t_ms *s, char **str)
{
	char	*key;
	char	*value;

	if (str[1] == NULL)
	{
		sort_env_list(&s->export);
		return (print_export(s->export));
	}
	key = get_key_from_str(str[1]);
	value = get_value_from_str(str[1]);
	if (!key)
		return (0);
	export_update(s->export, key, value);
	handle_kv_update(s->env, key, value);
	env_arr_update(s);
	env_paths(s, s->env_tmp);
	return (1);
}
