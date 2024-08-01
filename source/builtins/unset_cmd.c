/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:58:50 by dde-maga          #+#    #+#             */
/*   Updated: 2024/08/01 12:22:32 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	unset_clean(t_env *current)
{
	if (current->value)
	{
		free(current->value);
		current->value = NULL;
	}
	if (current->key)
	{
		free(current->key);
		current->key = NULL;
	}
	free(current);
	current = NULL;
}

void	unset_move(t_env *current)
{
	if (current->prev)
		current->prev->next = current->next;
	if (current->next)
		current->next->prev = current->prev;
}

void	unset_cmd_export(t_ms *s, char *args)
{
	t_env	*current;
	t_env	*tmp;

	current = s->export;
	while (current)
	{
		tmp = current->next;
		if ((ft_sw_builtins(current->key, args) == 0))
		{
			if (current->prev == NULL)
			{
				s->export = current->next;
				if (current->next)
					current->next->prev = NULL;
			}
			else if (current->next == NULL)
				current->prev->next = NULL;
			else
				unset_move(current);
			unset_clean(current);
			break ;
		}
		current = tmp;
	}
}

int	unset_cmd(t_ms *s, char **args)
{
	t_env	*tmp;
	int		i;

	i = 0;
	while (args[++i])
	{
		if (s->ast->argc > 1 && !is_valid_key(args[i]))
			export_cmd_error(s, "not valid identifier", args[i]);
		unset_aux(s, &tmp, args[i]);
		unset_cmd_export(s, args[i]);
		env_arr_update(s, args[i]);
		if (ft_strncmp(args[1], "PATH", ft_strlen(args[1])) != 0)
			env_paths(s, s->env_tmp);
	}
	return (1);
}
