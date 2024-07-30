/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:12:16 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/30 18:54:00 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* STRING MAGIC STARTS HERE */

// replaces -search- with -replace- on the range between *start and *end
// if end is NULL, searches until end of string.
void	ft_strrep_range(char *start, char *end, char search, char replace)
{
	char	*ptr;

	if (start == NULL)
		return ;
	ptr = start;
	if (end == NULL)
	{
		while (*ptr != '\0')
		{
			if (*ptr == search)
				*ptr = replace;
			ptr++;
		}
	}
	else
	{
		while (ptr < end)
		{
			if (*ptr == search)
				*ptr = replace;
			ptr++;
		}
	}
}

char	*reassemble_input(char *input)
{
	size_t	input_len;

	if (!input)
		return (input);
	input_len = ft_strlen(input);
	ft_strrep_range(input, NULL, DOLAR, '$');
	retokenizer(input, input + input_len);
	unglue_str(input, input + input_len);
	requoter(input + 1, input + input_len);
	return (remove_quotes(input, input));
}

void	skip_spaces(char *str, char *es)
{
	while (str < es && ft_strchr(SPACES, *str))
		str++;
}

void	glue_str(char *start, char *end)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(SPACES))
	{
		ft_strrep_range(start, end, SPACES[i], GLUE[i]);
		i++;
	}
}

void	unglue_str(char *start, char *end)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(SPACES))
	{
		ft_strrep_range(start, end, GLUE[i], SPACES[i]);
		i++;
	}
}
