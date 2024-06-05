#include "../../include/minishell.h"

int	add_node_export(t_env *env, char *key, char *value)
{
	t_env *new_node;
	t_env *export;

	new_node = (t_env *)malloc(sizeof(t_env));
	if(!new_node)
		error_msg("malloc (new env)");
	new_node->key = ft_strdup(key);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->prev = NULL;
	new_node->next = NULL;
	if (!env)
		env = new_node;
	else
	{
		export = env;
		while (export->next)
			export = export->next;
		export->next = new_node;
		new_node->prev = export;
	}
	return (1);
}

int	export_update(t_env *export, char *key, char *value)
{
	if(!is_valid_key(key))
	{
		printf("invalid Var Name");
		return (0);
	}
	if (!update_key(export, key, value))
	{
		if(!add_node_export(export,key,value))
			return (0);
	}
	return (1);
}
