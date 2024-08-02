/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:20:18 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/08/02 10:42:11 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	unset_cmd_aux(t_ms *s, t_env *current)
{
	s->env = current->next;
	if (current->next != NULL)
		current->next->prev = NULL;
}

void	unset_aux(t_ms *s, t_env **tmp, char *arg)
{
	t_env	*current;

	current = s->env;
	while (current)
	{
		*tmp = current->next;
		if ((ft_sw_builtins(current->key, arg) == 0) \
			&& ft_strcmp(current->key, "_") != 0)
		{
			if (current->prev == NULL)
				unset_cmd_aux(s, current);
			else if (current->next == NULL)
				current->prev->next = NULL;
			else
				unset_move(current);
			unset_clean(current);
			break ;
		}
		current = *tmp;
	}
}
