/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:58:59 by dde-maga          #+#    #+#             */
/*   Updated: 2024/07/11 10:25:55 by dde-maga         ###   ########.fr       */
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
	char	*key;

	key_len = delimiter - str;
	key = ft_substr(str, 0, key_len);
	return key;
}

//!! AQUI
// TODO Function has more than 25 lines
int	update_key(t_env *env, char *key, char *value)
{
	char	*value_tmp;
	t_env	*env_hold;
	int		key_found;

	env_hold = env;
	key_found = 0;
	while (env)
	{
		if (ft_sw_builtins(env->key, key) == 0)
		{
			key_found = 1;
			if (value)
			{
				if (env->value != NULL && ft_strcmp(value, env->value) == 0)
					break;
				value_tmp = ft_strdup(value);
				if (!value_tmp)
					return (0);
				free(env->value);
				env->value = value_tmp;
			}
			break;
		}
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

void free_key(char **key)
{
	if (key && *key)
	{
		free(*key);
		*key = NULL;
	}
}



// TODO Function has more than 25 lines
int export_cmd(t_ms *s, char **str)
{
	char *key = NULL;
	char *value = NULL;
	int i = 0;

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
		else
		{
			value = get_value_from_str(str[i]);
			export_update(s->export, key, value);
			handle_kv_update(s->env, key, value, 0);
			env_arr_update(s, NULL);
			env_paths(s, s->env_tmp);
			free(key);
			free(value);
			key = NULL;
			value = NULL;
		}
	}
	return 0;
}
