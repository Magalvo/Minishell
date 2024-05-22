
#include "../include/minishell.h"

/*
list related functions
*/


// takes a stack (t_header) then inits and appends nodes for all values
// bool	init_envp(t_header *a, char **values)
// {
// 	int		i;
// 	long	tmp;
// 	t_node	*new;

// 	i = 0;
// 	while (values[i])
// 	{
// 		tmp = atol_ps(values[i]);
// 		if (tmp == LONG_MAX)
// 			return (false);
// 		new = init_node(tmp);
// 		append_node(a, new);
// 		i++;
// 	}
// 	return (true);
// }

// create new node and set its value
// t_env	*init_node(int value)
// {
// 	t_node	*new_node;

// 	new_node = malloc(sizeof(t_node));
// 	if (!new_node)
// 		ft_putendl_fd("ops", 2);
// 	new_node->index = 0;
// 	new_node->value = value;
// 	new_node->prev = NULL;
// 	new_node->next = NULL;
// 	return (new_node);
// }

// t_cmd	*init_cmd(int value)
// {
// 	t_node	*new_node;

// 	new_node = malloc(sizeof(t_node));
// 	if (!new_node)
// 		ft_putendl_fd("ops", 2);
// 	new_node->index = 0;
// 	new_node->value = value;
// 	new_node->prev = NULL;
// 	new_node->next = NULL;
// 	return (new_node);
// }

// todo check if cmd starts with / or ./
void	init_paths(t_ms *s, char **ep)
{
	while (ft_strncmp(*ep, "PATH=", 5) != 0 && ep)
		ep++;
	s->paths = ft_split(*ep + 5, ':');
	if (s->paths == NULL)
		exit_minishell(s, "error getting paths");
	// s->cmdout = test_path(s, s->cmdout_args[0]);
}
// ? maybe needed, maybe not, depends on program flow
// char	*test_path(t_ms *s, char *cmd)
// {
// 	char	*path;
// 	char	*temp;
// 	int		i;

// 	i = 0;
// 	while (s->paths[i] != NULL)
// 	{
// 		if (s->paths[i][ft_strlen(s->paths[i]) - 1] != '/')
// 		{
// 			temp = ft_strjoin(s->paths[i], "/");
// 			path = ft_strjoin(temp, cmd);
// 			free(temp);
// 		}
// 		else
// 			path = ft_strjoin(s->paths[i], cmd);
// 		if (!path)
// 			return (NULL);
// 		// if (access(path, F_OK) != -1)	// file exists, execve checks if is executable
// 		if (access(path, F_OK | X_OK) != -1)	// execve won't run
// 			return (path);
// 		free(path);
// 		i++;
// 	}
// 	// return (cmd);
// 	return (ft_strdup(cmd));
// }
