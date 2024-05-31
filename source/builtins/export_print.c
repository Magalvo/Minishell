/* #include "../../include/minishell.h"

int	ft_keysum(const char *key)
{
	int	count;

	count = 0;
	while (*key)
		count += *key++;
	return(count);
}

int	print_exp(t_env *export)
{
	while(export)
	{
		if (export->value != NULL && export->value[0])
			printf("declare -x %s=%s\n", export->key, export->value);
		else   //?nao e suposto mostrar?
			printf("declare -x %s\n");
		export = export->next;
	}	
	return (0);
} */
/* 
void	node_swapping(t_env **head, t_env *node1, t_env *node2)
{
	static t_env	*n_prev1;
	static t_env	*n_prev2
	static t_env	*temp;

	if (node1 == node2)
		return ;
	
	
} */

/* int	print_export(t_ms *s)
{
	t_env	*env;
	t_env	*exported;
	t_env	*new_node;

	env=s->env;
	exported = NULL;
	while (env)
	{
		new_node = (t_env *)ft_calloc(sizeof(t_env));
		
	}

} */