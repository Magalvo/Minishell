/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:59:07 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/27 15:49:59 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//!===========================================
//? O sinal de = faz parte da key ou do value?

char	*env_paths(t_ms *ms, char **envp)
{
	char	**paths;
	char	*slash;
	int		i;
	int		found;

	i = 0;
	found = 0;
	slash = NULL;
	paths = NULL;
	if (ms->paths)
	{
		free_all_paths(ms->paths); 
		ms->paths = NULL;
	}
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)    //!HERE Removed '=' from PATH=
		{
			found = 1;
			paths = ft_split(envp[i] + 5, ':');
			break;
		}
		i++;
	}
	if (!found || !paths)
		paths = ft_split("/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin", ':');
	add_slash(slash, paths);
	ms->paths = paths;
	return (NULL);
}
/* char	*env_paths(t_ms *ms, char **envp)
{
	char	**paths;
	char	*slash;

	slash = NULL;
	paths = NULL;
	while (ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	if (*envp == NULL)
		return (NULL);
	paths = ft_split(*envp + 5, ':');
	if (!paths)
		return (NULL);
	add_slash(slash, paths);
	ms->paths = paths;
	return (NULL);
} */

char	*get_env_val(t_env *env, char *key, t_ms *s)
{
	int i;

	i = 0; 
	if (key[0] == '$' && key[1] != '\0')
			key = key + 1;
	if (ft_strncmp(key, "PATH", 4) == 0)
	{
		while (s->paths && s->paths[i])
		{
			ft_putstr_fd(s->paths[i], 1);
			if(s->paths[i + 1] != NULL)
				ft_putstr_fd(":", 1);
			i++;
		}
	}
	else
	{
		while (env)
		{
			if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
				return (env->value);
			env = env->next;
		}
	}
	return (NULL);	
}

//!! 49 LINHAS!!! Mas bem gastas
int env_cmd(t_ms *s, char **cmds)
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
					exit(EXIT_FAILURE);
				}
				execve(path, &cmds[2], s->env_tmp);
				perror("execve");
				exit(EXIT_FAILURE);
			}
			else
				waitpid(id, NULL, 0);
		}
	}
	else
	{
		env_cpy = s->env;												//* Print the current env if no command was given after -i
		while (env_cpy)
		{
			if (env_cpy->value != NULL)
				printf("%s=%s\n", env_cpy->key, env_cpy->value);
			env_cpy = env_cpy->next;
		}
	}
	return (1);
}


t_env *new_env_node(char *env_var) {
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
		return NULL;
	}
	key_len = delimiter - env_var;
	node->key = ft_strndup(env_var, key_len);
	if (!node->key) 
	{
		free(node);
		return NULL;
	}
	if (!ft_strncmp("SHLVL", node->key, 5)) {
		num = ft_atoi(delimiter + 1);
		node->value = ft_itoa(num + 1);
		if (!node->value) {
			free(node->key);
			free(node);
			return NULL;
		}
	} else {
		node->value = ft_strdup(delimiter + 1);
		if (!node->value) {
			free(node->key);
			free(node);
			return NULL;
		}
	}
	node->prev = NULL;
	node->next = NULL;
	return node;
}


void	init_env(t_ms *ms, char **envp)
{
	t_env	*head = NULL;
	t_env	*tail = NULL;
	t_env 	*new_node;
	int		i;
	
	i = 0;
	while (envp[i] != NULL)
	{
		new_node = new_env_node(envp[i]);
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
	free_env_list(ms->env);
	ms->env = head;
}
