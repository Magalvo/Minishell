#include "../../include/minishell.h"

char	*key_dup(char *env_var, size_t key_len)
{
	return	ft_strndup(env_var, key_len);
}

int	setting_value(t_env *node, char *delimiter)
{
	int num;

	if (!ft_strncmp("SHLVL", node->key, 5)) 
	{
		num = ft_atoi(delimiter + 1);
		node->value = ft_itoa(num + 1);
	} 
	else
		node->value = ft_strdup(delimiter + 1);
	if (!node->value)
	{
		free(node->key);
		free(node);
		return (0);
	}
	return (1);
}

void	free_node(t_env *node)
{
	if(node)
	{
		free(node->key);
		free(node->value);
		free(node);
	}
}

void	dup_and_close(int fd, int standard)
{
	dup2(fd, standard);
	close(fd);
}