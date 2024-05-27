/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:58:50 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/27 14:44:32 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* int	unset_cmd(t_ms *s, t_cmd *cmd)
{
	t_env	*env;
	
	env = s->env;
	while (env)
	{
		if (cmd->cmd_args[1] != NULL)
		{
			if (cmd->cmd_args[1] == env->key)
			{
				env->key = cmd->cmd_args[1];
				break;
			}
			env = env->next;
		}
		else
			return(error_msg("Unset need Args!"), 0);
	}
	return (1);
} */


/* int	unset_cmd_test(t_ms *s, char **cmds)
{
	t_env	*env;
	
	env = s->env;
	while (env)
	{
		if (cmd->cmd_args[1] != NULL)
		{
			if (cmd->cmd_args[1] == env->key)
			{
				env->key = cmd->cmd_args[1];
				break;
			}
			env = env->next;
		}
		else
			return(error_msg("Unset need Args!"), 0);
	}
	return (1);
} */
/* int	unset_cmd(t_ms *s, char **args)
{
	t_env *current;
	if (!args[1])
		return (0);
	current = s->env;
	while(current)
	{
		if ((current->key[ft_strlen(args[1])] == '=') &&
		 	(ft_strncmp(current->key, args[1], ft_strlen(args[1])) == 0))
		{
			printf("hey %s\n", current->key);
			if(current->next == NULL)
				current->prev->next = NULL;
			else
				current->prev->next = current->next;
				
			if(current->prev == NULL)
				current->next->prev = NULL;
			else
				current->next->prev = current->prev;
			free(current->value);
			free(current->key);
			free(current);
			return (1);
		}
		if (current->next == NULL)
			return (0);
		current = current->next;
	}
	return (1);
} */

void	unset_clean(t_env *current)
{
	free(current->value);
	free(current->key);
	free(current);
}

void	unset_move(t_env *current)
{
	current->prev->next = current->next;
	current->next->prev = current->prev;
}

int unset_cmd(t_ms *s, char **args) 
{
	t_env *current;

	current = s->env;
	while (current && args[1]) 
	{
		if ((current->key[ft_strlen(args[1])] == '=') &&
			(ft_strncmp(current->key, args[1], ft_strlen(args[1])) == 0)) 
		{
			if (current->prev == NULL) //! If the node to remove is the head
			{
				s->env = current->next;
				if (current->next != NULL)
					current->next->prev = NULL;
			} 
			else if (current->next == NULL) //! If the node to remove is the tail
				current->prev->next = NULL;
			else 
				unset_move(current);
			unset_clean(current);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

