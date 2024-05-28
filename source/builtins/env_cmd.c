/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:59:07 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/27 15:49:59 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//!===========================================
//? O sinal de = faz parte da key ou do value?

char	*get_env_val(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}


int	env_cmd(t_ms *s)
{
	t_env	*env;

	env = s->env;
	while(env)
	{
		if (env->value != NULL)
			printf("%s%s\n", env->key, env->value);
		env = env->next;
	}	
	return (1);
}


t_env	*new_env_node(char *env_var)
{
	t_env	*node;
	size_t	key_len;		//* new node to add to the stack
	char	*delimiter;		//*equal signn (=)

	node = ft_calloc(sizeof(t_env), 1);
	if(!node)
		error_msg("malloc (new env)");
	delimiter = ft_strchr(env_var, '=');
	if (!delimiter)
	{
		free(node);
		return (NULL);
	}
	delimiter++;
	key_len = (delimiter - env_var);
	node->key = ft_substr(env_var, 0, key_len);
	node->value = ft_strdup(delimiter);
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	init_env(t_ms *ms, char **envp)
{
	t_env	*head;		//! Referencias temporarias para manipulacao da lista
	t_env	*tail;		//! Nao estao na struct do env
	int		i;

	head = NULL;
	tail = NULL;
	i = -1;
	while (envp[++i] != NULL)
	{
		t_env	*new_node = new_env_node(envp[i]);
		if (!new_node)
			continue;
		if (!head)
		{
			head = new_node;
			tail = new_node;	
		}
		else
		{
			tail->next = new_node;
			new_node->prev = tail;
			tail = new_node;
		}	
	}
	ms->env = head;   //* pointer para o primeiro elemento da lista
}

