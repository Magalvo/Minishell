#include "../../include/minishell.h"

char	*get_key_from_str(const char *str)
{
	char *delimiter = ft_strchr(str, '=');
	if (delimiter)
		return (extract_key(str, delimiter));
	else
		return ft_strdup(str);
}

char	*get_value_from_str(const char *str)
{
	char *delimiter = ft_strchr(str, '=');
	if (delimiter)
		return (ft_strdup(delimiter + 1));
	else
		return (NULL);
}

int	handle_kv_update(t_env *env, char *key, char *value)
{
	if(!is_valid_key(key))
	{
		free(key);
		if(value)
			free(value);
		printf("invalid Var Name");
		return (0);
	}
	if (!update_key(env, key, value))
	{
		if(!add_new_node(env,key,value))
		{
			free(key);
			if(value)
				free(value);
			return (0);
		}
		else if (value)
			free (value);
	}
	free(key);
	return (1);
}

void	init_export(t_ms *ms, char **envp)
{
	t_env	*head;
	t_env	*tail;
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
	//free_env_list(ms->export);
	ms->export = head;
}

