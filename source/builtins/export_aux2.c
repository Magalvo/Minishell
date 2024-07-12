/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_aux2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:58:59 by dde-maga          #+#    #+#             */
/*   Updated: 2024/07/12 22:14:50 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_key(char *key)
{
	int	i;

	i = 1;
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	while (key[i] != '\0')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	*extract_key(const char *str, char *delimiter)
{
	size_t	key_len;
	char	*key;

	key_len = delimiter - str;
	key = ft_substr(str, 0, key_len);
	return (key);
}

void	free_key(char **key)
{
	if (key && *key)
	{
		free(*key);
		*key = NULL;
	}
}
