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
		if ((ft_sw_builtins(current->key, args[1]) == 0)) 
		{
			if (current->prev == NULL) 		//! If the node to remove is the head
			{
				s->env = current->next;
				if (current->next != NULL)
					current->next->prev = NULL;
			} 
			else if (current->next == NULL) //! If the node to remove is the tail
				current->prev->next = NULL;
			else							//! If the node to remove is in the middle
				unset_move(current);
			unset_clean(current);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

