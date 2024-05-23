/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:59:07 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/23 15:22:07 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//!===========================================
//? O sinal de = faz parte da key ou do value?


int	env_cmd(t_ms *s)
{
	t_env	*env;

	env = s->env;
	while(env)
	{
		if (env->value != NULL)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}	
	return (1);
}


/* int	env_cmd(t_ms *s)
{
	t_en **envp;

	envp = s->env_tmp;
	while(*envp)
		printf("%s\n", *envp++);
	return (1);
} */

t_env	*new_env_node(char *env_var)
{
	t_env	*node;
	size_t	key_len;		//* new node to add to the stack
	char	*delimiter;		//*equal signn (=)

	node = malloc(sizeof(t_env));
	if(!node)
		error_msg("malloc (new env)");
	delimiter = ft_strchr(env_var, '=');
	if (!delimiter)
	{
		free(node);
		return (NULL);
	}	
	key_len = delimiter - env_var;
	node->key = ft_substr(env_var, 0, key_len);
	node->value = ft_strdup(delimiter + 1);
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	init_env(t_ms *ms, char **envp)
{
	t_env	*head;		//! Referencias temporarias para manipulacao da lista
	t_env	*tail;		//! 
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (envp[i] != NULL)
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
		i++;
	}
	ms->env = head;   //* pointer para o primeiro elemento da lista
}

