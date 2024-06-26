/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:10:49 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/06/28 16:54:31 by dde-maga         ###   ########.fr       */
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
	if ((*(ps + 1) == '"' && is_quoted(input, ps) == E_DQUOTE)
		|| ft_strlen(key) == 0)
		return (*(ps) = 17, s->one_dolar = true, input);
	// if (*(ps + 1) == '"' && is_quoted(input, ps) == E_DQUOTE)
	// 	return (*(ps) = 17, input);
	if (*(ps + 1) == '"' && is_quoted(input, ps) == E_DQUOTE)
		return (*(ps) = 17, input);
	res = get_expanded(input, ps, val, ps + keylen);
	free (key);
	free (val);
	return(free(input), res);
}

char	*vars_sw(char *xp_input, char *pos, t_ms *s)
{
	if (*(pos + 1) == '{')	//}
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
