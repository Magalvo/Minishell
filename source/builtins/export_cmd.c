/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:58:59 by dde-maga          #+#    #+#             */
/*   Updated: 2024/07/30 17:28:08 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_and_update(t_env *env, char *key, char *value)
{
	char	*value_tmp;

	if (ft_sw_builtins(env->key, key) == 0)
	{
		if (value)
		{
			if (env->value != NULL && ft_strcmp(value, env->value) == 0)
				return (1);
			value_tmp = ft_strdup(value);
			if (!value_tmp)
				return (-1);
			free(env->value);
			env->value = value_tmp;
		}
		return (1);
	}
	return (0);
}

//!! AQUI
int	update_key(t_env *env, char *key, char *value)
{
	t_env	*env_hold;
	int		result;
	int		key_found;

	env_hold = env;
	key_found = 0;
	while (env)
	{
		result = check_and_update(env, key, value);
		if (result == 1)
		{
			key_found = 1;
			break;
		}
		else if (result == -1)
			return (0);
		env = env->next;
	}
	env = env_hold;
	return (key_found);
}

int	add_new_node(t_env *env, char *key, char *value)
{
	t_env	*env_cpy;
	t_env	*new_node;

	new_node = (t_env *)ft_calloc(sizeof(t_env), 1);
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
	int		i;

	i = 0;
	key = NULL;
	if (str[1] == NULL)
		return (sort_env_list(&s->export), print_export(s->export));
	while (str[++i])
	{
		key = get_key_from_str(str[i]);
		if (!key || !is_valid_key(key))
		{
			free_key(&key);
			export_cmd_error(s, ": not a valid identifier", str[i]);
		}
		// ! moved to other function because nilf
		else
			handle_key(s, str[i], key);
	}
	return (0);
}

void	handle_key(t_ms *s, char *str, char *key)
{
	char	*value;
	char	*append;
	char	*val;
	char	*val2;

	value = NULL;
	append = ft_strchr(str, '=');
	// ! comment next if else, keep: value = get_value_from_str(str);
	if (append && *(append - 1) == '+')
	{
		val = get_env_val(s->env, key, s);
		val2 = get_value_from_str(str);
		value = ft_strjoin(val, val2);
		free2(val, val2);
	}
	else
		value = get_value_from_str(str);
	export_update(s->export, key, value);
	handle_kv_update(s->env, key, value, 0);
	env_arr_update(s, NULL);
	env_paths(s, s->env_tmp);
	free2(key, value);
	key = NULL;
	value = NULL;
}
