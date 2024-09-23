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

int	aux_verify(t_cmd *cmd, t_ms *s)
{
	t_cmd	*cmd_h;

	cmd_h = cmd;
	while (cmd_h->cmd)
	{
		if (cmd_h->fd == 0)
		{
			if (check_read_acess(cmd_h, s))
				return (1);
		}
		else if (cmd_h->fd == 1)
		{
			if (access(cmd_h->file, F_OK) == 0)
			{
				if (access(cmd_h->file, W_OK) != 0)
				{
					s->file_err += 1;
					cmd_h->inv_file = 1;
				}
			}
		}
		cmd_h = cmd_h->cmd;
	}
	return (0);
}

void	heredoc_handler(t_ms *s, t_cmd *cmd, int *fd_in, int *temp_fd)
{
	if (cmd->type == HEREDOC)
	{
		if (cmd->cmd && cmd->cmd->type == 2)
			unclose0(s, cmd, fd_in, temp_fd);
		else if (*fd_in < 2)
			*fd_in = cmd->fd;
	}
}
