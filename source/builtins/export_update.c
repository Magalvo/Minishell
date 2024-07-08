/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:24:02 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/08 19:15:25 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	add_node_export(t_env *env, char *key, char *value)
{
	t_env	*new_node;
	t_env	*export;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (ft_putstr_fd("malloc (new env)", 2), 0);
	new_node->key = ft_strdup(key);
	if (!new_node)
		return (free(new_node), 0);
	if (value)
	{
		new_node->value = ft_strdup(value);
		if (!new_node->key)
			return (free(new_node->key), free(new_node), 0);
	}
	else
		new_node->value = NULL;
	new_node->prev = NULL;
	new_node->next = NULL;
	if (!env)
		env = new_node;
	else
	{
		export = env;
		while (export->next)
			export = export->next;
		export->next = new_node;
		new_node->prev = export;
	}
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
