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

int	handle_key_value_update(t_ms *s, char *key, char *value)
{
	if(!is_valid_key(key))
	{
		free(key);
		if(value)
			free(value);
		printf("invalid Var Name");
		return (0);
	}
	if (!update_key(s->env, key, value))
	{
		if(!add_new_node(s,key,value))
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
	return (0);
}
void	init_export(t_ms *ms, char **envp)
{
	t_env	*head = NULL;
	t_env	*tail = NULL;
	int		i;

	for (i = 0; envp[i] != NULL; i++)
	{
		t_env *new_node = new_env_node(envp[i]);
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
	}
	ms->export = head;
}