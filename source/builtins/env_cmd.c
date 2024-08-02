/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:59:07 by dde-maga          #+#    #+#             */
/*   Updated: 2024/08/02 10:42:26 by dde-maga         ###   ########.fr       */
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

/* t_env *new_env_node(char *env_var)
{
	t_env *node;
	size_t key_len;
	char *delimiter;
	int num;

	node = ft_calloc(sizeof(t_env), 1);
	if (!node)
		error_msg("malloc (new env)");
	delimiter = ft_strchr(env_var, '=');
	if (!delimiter) {
		free(node);
		return (NULL);
	}
	key_len = delimiter - env_var;
	node->key = ft_strndup(env_var, key_len);
	if (!node->key)
	{
		free(node);
		return (NULL);
	}
	if (!ft_strncmp("SHLVL", node->key, 5)) {
		num = ft_atoi(delimiter + 1);
		node->value = ft_itoa(num + 1);
		if (!node->value) {
			free(node->key);
			free(node);
			return (NULL);
		}
	} else {
		node->value = ft_strdup(delimiter + 1);
		if (!node->value) {
			free(node->key);
			free(node);
			return (NULL);
		}
	}
	node->prev = NULL;
	node->next = NULL;
	return (node);
} */

//!! 49 LINHAS!!! Mas bem gastas
/* int env_cmd(t_ms *s, char **cmds)
{
	char	*path;
	int		id;
	t_env 	*env_cpy;

	id = 0;
	path = NULL;
	if (cmds[1] && cmds[1][0] == '-' && cmds[1][1] == 'i' && cmds[1][2] == '\0')
	{
		if (s->env_tmp)
		{
				clear_env(s->env_tmp);
				s->env_tmp = NULL;
		}
		s->env_tmp = null_env_init();
		if (cmds[2])
		{
			id = fork();
			if (id < 0)
				return (exit_minishell(s, "error"), 0);
			if (id == 0)
			{
				path = cmd_path(s->paths, cmds[2], s);
				if (!path)
				{
					ft_putstr_fd("command not found\n", 2);
					set_exit(127, s);
				}
				execve(path, &cmds[2], s->env_tmp);
				set_exit(127, s);
			}
			else
				waitpid(id, NULL, 0);
		}
	}
	else
	{
		env_cpy = s->env;
		while (env_cpy)
		{
			if (env_cpy->value != NULL)
				printf("%s=%s\n", env_cpy->key, env_cpy->value);
			env_cpy = env_cpy->next;
		}
	}
	return (1);
} */

/* void	init_env(t_ms *ms, char **envp)
{
	t_env	*head;
	t_env	*tail;
	t_env 	*new_node;
	int i;

	i = 0;
	head = NULL;
	tail = NULL;
	while (envp[i] != NULL)
	{
		new_node = new_env_node(envp[i]);
		if (!new_node)
			continue ;
		if (new_node)
			init_aux(&head, &tail, new_node);
		i++;
	}
	free_env_list(ms->env);
	ms->env = head;
} */
