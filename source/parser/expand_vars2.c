/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:10:49 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/06/27 16:49:50 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand_dolar(char *input, char *ps, t_ms *s)
{
	char	*end;
	char	*key;
	char	*val;
	char	*res;
	int		keylen;

	end = ps;
	keylen = 0;
	val = NULL;
	while (ft_isalpha(*++end) || *end == '_')
		;
	key = ft_substr(input, (ps + 1) - input, (end - 1) - ps);
	if (key)
	{
		keylen = (ft_strlen(key)) + 1;
		val = get_env_val(s->env, key, s);
		glue_str(val, val + ft_strlen(val));
	}
	if (*(ps + 1) == '"' && is_quoted(input, ps) == E_DQUOTE)
		return (input);
		// return (*(ps + 1) = (char)17, input);
	res = get_expanded(input, ps, val, ps + keylen);
	free (key);
	//free (val);
	return(free(input), res);
}

char	*remove_quotes(char *input, char *pos)
{
	char	*qt_pos;
	char	*res1;
	char	*res2;
	bool	is_qt;

	is_qt = false;
	qt_pos = get_first_quote(pos);
	if (!qt_pos)
		return (input);
	if (*qt_pos == QUOTE)
		is_qt = true;
	// else if (*qt_pos == DQUOTE)
		// is_qt = false;
	res1 = get_expanded(input, qt_pos, NULL, qt_pos + 1);
	free(input);
	if (is_qt)
		qt_pos = ft_strchr(res1, QUOTE);
	else
		qt_pos = ft_strchr(res1, DQUOTE);
	res2 = get_expanded(res1, qt_pos, NULL, qt_pos + 1);
	int offset = qt_pos - res1;
	free(res1);
	remove_quotes(res2, res2 + offset);
	return (res2);
}
