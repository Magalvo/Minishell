/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:15:08 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/05 20:19:45 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
Enclosing characters in single quotes (') preserves the literal value
of each character within the quotes.
A single quote may not occur between single quotes,
even when preceded by a backslash.

Enclosing characters in double quotes (") preserves the literal value
of all characters within the quotes, with the exception of ($), ('), (\).
The characters ($) and (') retain their special meaning within double quotes.
The backslash retains its special meaning only when followed
by one of the following characters: ($), ('), ("), (\), or newline (\n).
Within double quotes, backslashes that are followed
by one of these characters are removed
*/

// enum s_quote_type { NONE 0, E_QUOTE 1, E_DQUOTE 2 };
// # define QUOTE '		DQUOTE "
// key[0] unused, key[1] for quote, key[2] for dquote
// TODO too many lines // implement the XOR ^= trick here

int	*magic_key(void)
{
	int	*key;

	key = malloc(3 * sizeof(int));
	if (key != NULL)
	{
		key[0] = NONE;
		key[1] = NONE;
		key[2] = NONE;
	}
	return (key);
}

int	syntax_quotes(const char *str)
{
	int	*key;

	key = magic_key();
	while (*str)
	{
		if (*str == QUOTE)
		{
			if (key[E_DQUOTE] == NONE)
				(key[E_QUOTE] ^= E_QUOTE);
		}
		else if (*str == DQUOTE)
		{
			if (key[E_QUOTE] == NONE)
				(key[E_DQUOTE] ^= E_DQUOTE);
		}
		str++;
	}
	if (key[E_QUOTE] != NONE || key[E_DQUOTE] != NONE)
		return (free(key), -1);
	return (free(key), 0);
}

// check what type of quotes a ptr on a string has, if any
int	is_quoted(const char *str, const char *totest)
{
	int	quote;

	quote = NONE;
	if (totest == NULL)
		return (-1);
	while (str < totest)
	{
		if (*str == QUOTE)
		{
			if (quote == NONE)
				quote = E_QUOTE;
			else if (quote == E_QUOTE)
				quote = NONE;
		}
		else if (*str == DQUOTE)
		{
			if (quote == NONE)
				quote = E_DQUOTE;
			else if (quote == E_DQUOTE)
				quote = NONE;
		}
		str++;
	}
	return (quote);
}

char	*get_first_quote(char *input)
{
	char	*qt;
	char	*dqt;
	char	*pos;

	pos = NULL;
	if (!input)
		return (pos);
	qt = ft_strchr(input, '\'');
	dqt = ft_strchr(input, '"');
	if (qt && dqt)
	{
		pos = qt;
		if (qt > dqt)
			pos = dqt;
	}
	else if (qt)
		pos = qt;
	else if (dqt)
		pos = dqt;
	return (pos);
}

char	*remove_quotes(char *input, char *pos)
{
	char	*qt_pos;
	int		offset;
	bool	is_qt;

	is_qt = false;
	qt_pos = get_first_quote(pos);
	if (!qt_pos)
		return (input);
	if (*qt_pos == QUOTE)
		is_qt = true;
	get_shrinked(input, qt_pos);
	if (is_qt)
		qt_pos = ft_strchr(input, QUOTE);
	else
		qt_pos = ft_strchr(input, DQUOTE);
	get_shrinked(input, qt_pos);
	offset = qt_pos - input;
	remove_quotes(input, input + offset);
	return (input);
}
