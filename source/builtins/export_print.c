/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:23:48 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/08 19:06:45 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_exp(t_env *export)
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

int	print_export(t_env *env)
{
	return (print_exp(env));
}

void	swap_env_data(t_env *a, t_env *b)
{
	char	*temp_key;
	char	*temp_value;

	temp_key = a->key;
	temp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = temp_key;
	b->value = temp_value;
}

int	compare_keys(char *a, char *b)
{
	int	len;

	if (ft_strlen(a) > ft_strlen(b))
		len = ft_strlen(a);
	else
		len = ft_strlen(b);
	return (ft_strncmp(a, b, len) > 0);
}

void	sort_env_list(t_env **head)
{
	int		swapped;
	t_env	*ptr;
	t_env	*lptr;

	lptr = NULL;
	if (*head == NULL)
		return ;
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
