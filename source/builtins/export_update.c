/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:24:02 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/08/02 10:40:01 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*create_new_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!new_node)
		return (ft_putstr_fd("malloc (new env)", 2), NULL);
	new_node->key = ft_strdup(key);
	if (!new_node)
		return (free(new_node), NULL);
	if (value)
	{
		new_node->value = ft_strdup(value);
		if (!new_node->key)
		{
			free(new_node->key);
			free(new_node);
			return (NULL);
		}
	}
	else
		new_node->value = NULL;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	append_env(t_env *env, t_env *new_node)
{
	t_env	*export;

	export = env;
	while (export->next)
		export = export->next;
	export->next = new_node;
	new_node->prev = export;
}

int	add_node_export(t_env *env, char *key, char *value)
{
	t_env	*new_node;

	new_node = create_new_node(key, value);
	if (!new_node)
		return (0);
	if (!env)
		env = new_node;
	else
		append_env(env, new_node);
	return (1);
}

int	export_update(t_env *export, char *key, char *value)
{
	if (!is_valid_key(key))
	{
		ft_putstr_fd(" not a valid identifier", 2);
		return (0);
	}
	if (!update_key(export, key, value))
	{
		if (!add_node_export(export, key, value))
			return (0);
	}
	return (1);
}

int	is_str_print(char *value)
{
	if (!value)
		return (0);
	while (*value)
	{
		if (!isprint((unsigned char)*value))
			return (0);
		value++;
	}
	return (1);
}
