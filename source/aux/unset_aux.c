/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:20:18 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/09/20 10:03:57 by dde-maga         ###   ########.fr       */
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

int	export_unset_error(t_ms *s, char *msg, char *key)
{
	(void)s;
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd("': ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

void	redir_aux(t_cmd *cmd, int fd_in)
{
	if (fd_in > 2)
		close_fd(&fd_in);
	fd_in = cmd->fd;
}