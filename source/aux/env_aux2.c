/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_aux2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:20:37 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/06/27 18:49:51 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* moved to parser
int	here_doc(char *dli, t_ms *s, t_cmd *cmd)
{
	int		file;
	char	*line;
	int		in_file;

	(void)s;
	(void)cmd;
	file = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file == -1)
		error_msg("Error opening here_doc");
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (line == NULL || ft_strncmp(dli, line, ft_strlen(dli)) == 0)
			break ;
		ft_putstr_fd(line, file);
		free(line);
	}
	free(line);
	close(file);
	in_file = open(".here_doc", O_RDONLY);
	if (in_file < 0)
		error_msg("opening here_doca");
	return (in_file);
}
*/

/* void	init_aux(t_env **head, t_env **tail, t_env *new_node)
{
	if (!*head)
	{
		*head = new_node;
		*tail = new_node;
	}
	else
	{
		(*tail)->next = new_node;
		new_node->prev = *tail;
		*tail = new_node;
	}
} */

void	init_aux(t_env **head, t_env **tail, t_env *new_node)
{
	if (*tail)
	{
		(*tail)->next = new_node;
		new_node->prev = *tail;
		*tail = new_node;
	}
	else
	{
		*head = new_node;
		*tail = new_node;
	}
}

char	*env_paths(t_ms *ms, char **envp)
{
	char	**paths;
	char	*slash;
	int		i;
	int		found;

	i = -1;
	found = 0;
	slash = NULL;
	paths = NULL;
	if (ms->paths)
		free_all_paths(ms->paths);
	while (envp[++i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			found = 1;
			paths = ft_split(envp[i] + 5, ':');
			break ;
		}
	}
	if (!found || !paths)
		paths = ft_split(MIN_PATH, ':');
	add_slash(slash, paths);
	ms->paths = paths;
	return (NULL);
}

char	*get_env_val(t_env *env, char *key, t_ms *s)
{
	int	i;

	i = 0;
	if (ft_strncmp(key, "PATH", 4) == 0)
	{
		while (s->paths && s->paths[i])
		{
			ft_putstr_fd(s->paths[i], 1);
			if (s->paths[i + 1] != NULL)
				ft_putstr_fd(":", 1);
			i++;
		}
	}
	else
	{
		while (env)
		{
			if (ft_strncmp(env->key, key, ft_strlen(key)) == 0 && \
				ft_strlen(env->key) == ft_strlen(key))
				return (env->value);
			env = env->next;
		}
	}
	return (NULL);
}

char	**env_convert(t_env *env)
{
	int		i;
	int		ctd;
	char	**env_array;
	t_env	*current;

	ctd = 0;
	env_array = create_env_array(env, &ctd);
	current = env;
	i = 0;
	while (i < ctd)
	{
		env_array[i] = join_key_value(current->key, current->value);
		if (!env_array[i])
		{
			free_env_array(env_array);
			error_msg("malloc join key value");
		}
		current = current->next;
		i++;
	}
	env_array[ctd] = NULL;
	return (env_array);
}

char	**create_env_array(t_env *env, int *ctd_ptr)
{
	t_env	*current;
	char	**env_array;

	*ctd_ptr = 0;
	current = env;
	while (current)
	{
		(*ctd_ptr)++;
		current = current->next;
	}
	env_array = create_dptr(*ctd_ptr);
	if (!env_array)
		error_msg ("malloc env array");
	return (env_array);
}
