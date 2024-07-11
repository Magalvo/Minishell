/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tests2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:15:08 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/11 14:51:47 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	syntax_quotes(const char *str)
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
		return (free(key), false);
	return (free(key), true);
}

bool	syntax_redir(char *str, char *end)
{
	int		tok;
	char	*ps_cpy;
	char	*es_cpy;

	ps_cpy = str;
	es_cpy = end;
	while (true)
	{
		tok = get_token(&str, end, 0, 0);
		if (tok == 0)
			break ;
		if (peek(&str, end, "<>") && ft_strchr("<>", tok))
		{
			str = ps_cpy;
			end = es_cpy;
			return (false);
		}
	}
	(void)tok;
	str = ps_cpy;
	end = es_cpy;
	return (true);
}
