/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:23:29 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/10 11:08:30 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_key_from_str(const char *str)
{
	char	*delimiter;
	char	*key;

	delimiter = ft_strchr(str, '=');
	if (delimiter)
		key = extract_key(str, delimiter);
	else
		key = ft_strdup(str);
	return (key);
}

char	*get_value_from_str(char *str)
{
	char	*equal_sign;
	char	*value;

	equal_sign = ft_strchr(str, '=');
	if (!equal_sign)
		return (NULL);
	equal_sign += 1;
	value = ft_strdup(equal_sign);
	equal_sign -= 1;
	return (value);
}

int	handle_kv_update(t_env *env, char *key, char *value, int tog)
{
	if (!is_valid_key(key))
	{
		free(key);
		key = NULL;
		if (value)
		{
			free(value);
			value = NULL;
		}
		return (printf(" not a valid identifier"), 0);
	}
	if (!update_key(env, key, value))
	{
		if (!add_new_node(env, key, value))
		{
			return (0);
		}
	}
	if (tog)
	{
		free(key);
		key = NULL;
	}
	return (1);
}

void	init_list(t_env **list, char **envp)
{
	int		i;
	t_env	*head;
	t_env	*tail;
	t_env	*new_node;

	i = 0;
	head = NULL;
	tail = NULL;
	while (envp[i] != NULL)
	{
		new_node = new_env_node(envp[i]);
		if (!new_node)
		{
			free_env_list(head);
			return ;
		}
		init_aux(&head, &tail, new_node);
		i++;
	}
	if (*list)
		free_env_list(*list);
	*list = head;
}

/* void	init_export(t_ms *ms, char **envp)
{
	int		i;
	t_env	*head;
	t_env	*tail;
	t_env 	*new_node;

	i = 0;
	head = NULL;
	tail = NULL;
	while (envp[i] != NULL)
	{
		new_node = new_env_node(envp[i]);
		if (!new_node)
			continue ;
		if (new_node)
			init_aux(&head, &tail, new_node);
		i++;
	}
	free_env_list(ms->export);
	ms->export = head;
} */
