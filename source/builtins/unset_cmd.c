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
	if (current->value)
		free(current->value);
	if (current->key)
		free(current->key);
	free(current);
}

void	unset_move(t_env *current)
{
	current->prev->next = current->next;
	current->next->prev = current->prev;
}

//! If the node to remove is the head
//! If the node to remove is the tail
//! If the node to remove is in the middle
void	unset_cmd_export(t_ms *s, char **args)
{
	t_env	*current;

	current = s->export;
	while (current && args[1])
	{
		if ((ft_sw_builtins(current->key, args[1]) == 0))
		{
			if (current->prev == NULL)
			{
				s->export = current->next;
				if (current->next != NULL)
					current->next->prev = NULL;
			}
			else if (current->next == NULL)
				current->prev->next = NULL;
			else
				unset_move(current);
			unset_clean(current);
			return ;
		}
		current = current->next;
	}
}

void	unset_cmd_aux(t_ms *s, t_env **current)
{
	s->env = (*current)->next;
	if ((*current)->next != NULL)
		(*current)->next->prev = NULL;
}

//! If the node to remove is the head
//! If the node to remove is the tail
//! If the node to remove is in the middle
int	unset_cmd(t_ms *s, char **args)
{
	t_env	*current;

	current = s->env;
	while (current && args[1])
	{
		if ((ft_sw_builtins(current->key, args[1]) == 0) &&
			ft_strncmp(current->key, "_", ft_strlen(current->key)))
		{
			if (current->prev == NULL)
				unset_cmd_aux(s, &current);
			else if (current->next == NULL)
				current->prev->next = NULL;
			else
				unset_move(current);
			unset_clean(current);
			break ;
		}
		current = current->next;
	}
	unset_cmd_export(s, args);
	env_arr_update(s, args[1]);
	//if (ft_strncmp(args[1], "PATH", ft_strlen(args[1])) != 0)
	//env_paths(s, s->env_tmp);
	return (1);
}
