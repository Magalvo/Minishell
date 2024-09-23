/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:59:07 by dde-maga          #+#    #+#             */
/*   Updated: 2024/09/23 15:24:22 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_current_env(t_env *env)
{
	while (env)
	{
		if (env->value != NULL)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void	execute_command(t_ms *s, t_cmd *cmd, char **cmds)
{
	pid_t	id;

	check_signal(IGNORE);
	id = fork();
	if (id < 0)
		exit_minishell(s, "error");
	if (id == 0)
	{
		check_signal(CHILD);
		cmds++;
		cmds++;
		exec_one(s, cmds);
		exit_minishell(s, NULL);
	}
	else
		wait_till_end(s, id, cmd);
}

void	clear_env_handler(t_ms *s)
{
	if (s->env_tmp)
	{
		clear_env(s->env_tmp);
		s->env_tmp = NULL;
	}
	s->env_tmp = null_env_init();
}

int	env_cmd(t_ms *s, char **cmds)
{
	if (cmds[1] && cmds[1][0] == '-' && cmds[1][1] == 'i' && cmds[1][2] == '\0')
	{
		if (cmds[2])
		{
			clear_env_handler(s);
			execute_command(s, s->ast, cmds);
		}
	}
	else if (cmds[1])
	{
		s->exit_stat = 127;
		return (not_found(cmds[1], 127, s), 1);
	}
	else
		print_current_env(s->env);
	return (1);
}

//!!! ADDED + 1
t_env	*new_env_node(char *env_var)
{
	t_env	*node;
	char	*delimiter;

	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (ft_putstr_fd("malloc (new env)", 2), NULL);
	delimiter = ft_strchr(env_var, '=');
	if (!delimiter)
		return (free(node), NULL);
	node->key = key_dup(env_var, delimiter - env_var);
	if (!node->key)
		return (free(node), NULL);
	if (!setting_value(node, delimiter))
		return (free_node(node), NULL);
	node->prev = NULL;
	node->next = NULL;
	return (node);
}
