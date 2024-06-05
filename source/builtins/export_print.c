#include "../../include/minishell.h"

int print_exp(t_env *export) 
{
	while (export) 
	{
		if (export->value != NULL)
		{
			printf("declare -x %s=\"%s\"\n", export->key, export->value);
		}
		else
		{
			printf("declare -x %s\n", export->key);
		}	
		export = export->next;
	}
	return (1);
}

int print_export(t_env *env) {
	return print_exp(env);
}

void swap_env_data(t_env *a, t_env *b) 
{
	char *temp_key;
	char *temp_value;

	temp_key = a->key;
	temp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = temp_key;
	b->value = temp_value;
}

int compare_keys(char *a, char *b) 
{
	int len;
	if (ft_strlen(a) > ft_strlen(b))
		len = ft_strlen(a);
	else
		len = ft_strlen(b);
	return (ft_strncmp(a, b, len) > 0); 
}

void sort_env_list(t_env **head) 
{
	int	swapped;
	t_env	*ptr;
	t_env	*lptr = NULL;

	if (*head == NULL)
		return;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr = *head;
		while (ptr->next != lptr) 
		{
			if (compare_keys(ptr->key, ptr->next->key)) 
			{
				swap_env_data(ptr, ptr->next);
				swapped = 1;
			}
			ptr = ptr->next;
		}
		lptr = ptr;
	}
}



/*  int	print_export(t_env *export)
{
	while (export)
	{
		if (export->value != NULL && export->value[0])
			printf("declare -x %s=\"%s\"\n", export->key, export->value);
		else
			printf("declare -x %s\n", export->key);
		export = export->next;
	}
	return (0);
} */
/*
t_env *list_cpy(t_env *var)
{
	t_env *out;

	while (var != NULL)
	{

	}
}

int sort_list(t_env *list)
{
	t_env *temp;
	t_env *out;

	out = list_cpy(list);
	while (list)
	{
		temp = list->next;
		while (temp)
		{
			if (compare_func)
			{
				
			}
		}
		list = list->next
	}
	
} */

/* int	envio_ex(t_env	*env)
{
	t_env	*cpy;
	t_env	*exported;
	t_env	*lowest_node;

	cpy = env;
	lowest_node = env;
	while (cpy)
	{
		if(lowest_node > cpy->key[0])
			lowest_node = cpy->key;
		cpy = cpy->next;
	}

} */

/* #include "../../include/minishell.h"

int	print_exp(t_env *export)
{
	while (export)
	{
		if (export->value != NULL && export->value[0])
			printf("declare -x %s=\"%s\"\n", export->key, export->value);
		else
			printf("declare -x %s\n", export->key);
		export = export->next;
	}
	return (0);
}

void	swap_nodes(t_env **head, t_env *node1, t_env *node2)
{
	t_env *prev1 = NULL;
	t_env *prev2 = NULL;
	t_env *temp = *head;

	if (node1 == node2)
		return;

	// Find the previous nodes of node1 and node2
	while (temp && temp != node1 && temp != node2)
	{
		if (temp->next == node1)
			prev1 = temp;
		if (temp->next == node2)
			prev2 = temp;
		temp = temp->next;
	}

	// Swap previous pointers
	if (prev1)
		prev1->next = node2;
	else
		*head = node2;
	if (prev2)
		prev2->next = node1;
	else
		*head = node1;

	// Swap next pointers
	temp = node1->next;
	node1->next = node2->next;
	node2->next = temp;
}

void	sort_env_list(t_env **head)
{
	int swapped;
	t_env *ptrI;
	t_env *Iptr;

	if (*head == NULL)
		return;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptrI = *head;
		Iptr = NULL;
		while (ptrI->next != Iptr)
		{
			if (strcmp(ptrI->key, ptrI->next->key) > 0)
			{
				swap_nodes(head, ptrI, ptrI->next);
				swapped = 1;
			}
			ptrI = ptrI->next;

			// Check if ptrI became NULL after moving to next node
			if (!ptrI)
				break;
		}
		Iptr = ptrI;
	}
}

int	print_export(t_ms *s)
{
	t_env	*env = s->env;
	t_env	*env_copy = NULL;
	t_env	*new_node;
	t_env	*copy_tail = NULL;

	while (env)
	{
		new_node = (t_env *)malloc(sizeof(t_env));
		if (!new_node)
			return (-1);

		new_node->key = ft_strdup(env->key);
		if (env->value != NULL)
			new_node->value = ft_strdup(env->value);
		else
			new_node->value = NULL;
		new_node->next = NULL;

		if (env_copy == NULL)
		{
			env_copy = new_node;
			copy_tail = new_node;
		}
		else
		{
			copy_tail->next = new_node;
			copy_tail = new_node;
		}

		env = env->next;
	}

	sort_env_list(&env_copy);
	print_exp(env_copy);

	// Free the copied list
	while (env_copy)
	{
		new_node = env_copy;
		env_copy = env_copy->next;
		free(new_node->key);
		free(new_node->value);
		free(new_node);
	}

	return (0);
} */
