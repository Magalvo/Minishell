/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:10:49 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/06/26 17:12:08 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// TODO can delete?
// ! no longer used
char	*expand_dolar_loop(char *input, t_ms *s)
{
	char	*start;
	// char	*end;
	// char	*key;
	char	*res;

	start = ft_strnstr(input, "$", ft_strlen(input));
	while (start != NULL && (*(char *)start + 1 != '?' && *(char *)start + 1 != '0' &&
		!ft_strchr(SPACES, *(char *)(start + 1))))
	{
		if (start && !chr_betw(input, start, '\''))
		{
			res = expand_dolar(input, start, s);
			// end = start;
			// while (ft_isalpha(*++end) || *end == '_')
			// 	;
			// key = ft_substr(input, start - input, end - start);
			// res = get_expanded(input, start, get_env_val(s->env, key, s), /*\*/
			// 		start + (ft_strlen(key)));
			// free (key);
			// free (input);
			input = res;
		}
		start = ft_strnstr(input, "$", ft_strlen(input));
	}
	res = ft_strdup(input);
	return(free(input), res);
}

char	*expand_dolar(char *input, char *ps, t_ms *s)
{
	char	*end;
	char	*key;
	char	*res;
	int		keylen;

	end = ps;
	keylen = 0;
	while (ft_isalpha(*++end) || *end == '_')
		;
	key = ft_substr(input, (ps + 1) - input, (end - 1) - ps);
	if (key)
		keylen = (ft_strlen(key)) + 1;
	res = get_expanded(input, ps, get_env_val(s->env, key, s), \
			ps + keylen);
	free (key);
	return(free(input), res);
}

char	*remove_quotes(char *input)
{
	char	*qt_pos;
	char	*res1;
	char	*res2;
	bool	is_qt;

	is_qt = false;
	qt_pos = get_first_quote(input);
	if (!qt_pos)
		return (input);
	if (*qt_pos == QUOTE)
		is_qt = true;
	else if (*qt_pos == DQUOTE)
		is_qt = false;

	res1 = get_expanded(input, qt_pos, NULL, qt_pos + 1);
	free(input);
	if (is_qt)
		qt_pos = ft_strchr(res1, QUOTE);
	else
		qt_pos = ft_strchr(res1, DQUOTE);
	res2 = get_expanded(res1, qt_pos, NULL, qt_pos + 1);
	free(res1);
	return (res2);
}
