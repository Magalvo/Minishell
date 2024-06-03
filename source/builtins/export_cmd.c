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


int update_key(t_env *env, char *key, char *value) 
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

int	add_new_node(t_ms *s, char *key, char *value)
{
	t_env *new_node; //= new_env_node(key,value);
	t_env *env;

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
		{
			env = env->next;
		}	
		env->next = new_node;
		new_node->prev = env;
	}
	return (1);
}

int export_cmd(t_ms *s, char **str)
{
	char	*key;
	char	*value;
	char	*delimiter;

	if (str[1] == NULL)
	{
		sort_env_list(&s->env);
		return (print_export(s->env));
	}
		
	delimiter = ft_strchr(str[1], '=');
	if (delimiter)
	{
		key = extract_key(str[1], delimiter);
		value = ft_strdup(delimiter + 1);
	}
	else
	{
		key = ft_strdup(str[1]);
		value = NULL;
	}
	if (!key)
        return (0);
	if (!is_valid_key(key))
	{
		free(key);
		if (value)
			free(value);
		return (printf("Invalid variable name\n"), 0);
	}
	if (!update_key(s->env, key, value))
	{
		if (!add_new_node(s, key, value))
			{
				free(key);
				if (value)
					free(value);
				return (0);
			}
	}
	else if (value)
		free(value);
	free(key);
	return (1);
}



