/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:10:49 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/13 00:32:53 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// expands $VAR, safeguarding empty and quoted $VAR
char	*expand_dolar(char *input, char *ps, t_ms *s)
{
	char	*end;
	char	*key;
	char	*val;
	char	*res;

	end = ps;
	val = NULL;
	while (ft_isalpha(*++end) || *end == '_')
		;
	key = ft_substr(input, (ps + 1) - input, (end - 1) - ps);
	if (key)
	{
		val = get_env_val(s->env, key, s);
		if (val == NULL)
			val = EMPTY_STR;
		glue_str(val, val + ft_strlen(val));
	}
	if (*(ps + 1) == '"' && is_quoted(input, ps) == E_DQUOTE)
		return (free(key), *(ps) = DOLAR, input);
	res = get_expanded(input, ps, val, ps + ft_strlen(key) + 1);
	if (!(val[0] == EMPTY))
		free(val);
	return (free(key), free(input), res);
}

// case switch for $VAR specific cases, returns expanded string
char	*vars_sw(char *xp_input, char *pos, t_ms *s)
{
	if (pos == NULL)
		return (xp_input);
	if (*(pos + 1) == '{')
		xp_input = expand_curly(xp_input, pos, s);
	else if (*(pos + 1) == '$')
		xp_input = expand_pid(xp_input, pos, s);
	else if (*(pos + 1) == '?')
		xp_input = expand_exit_stat(xp_input, pos, s);
	else if (*(pos + 1) == '_')
		xp_input = expand_last_cmd(xp_input, pos, s);
	else if (*(pos + 1) == '0')
		xp_input = expand_self(xp_input, pos, s);
	else
		xp_input = expand_dolar(xp_input, pos, s);
	return (xp_input);
}
