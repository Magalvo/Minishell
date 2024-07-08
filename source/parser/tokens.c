/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:17:12 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/08 19:41:43 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	sw_get_tilde(char **str)
{
	if (!**str)
		return (0);
	else if (**str == '&')
	{
		if (*++*str == '&')
			return (++str, 'N');
	}
	else if (**str == '<')
	{
		if (*++*str == '<')
		{
			++*str;
			return ('H');
		}
		return ('<');
	}
	else if (**str == '>')
	{
		if (*++*str == '>')
			return (++str, '+');
		return ('>');
	}
	else
		return ('a');
	return (0);
}

int	sw_get_token(char **str)
{
	if (!**str)
		return (0);
	else if (**str == '<')
	{
		if (*++*str == '<')
			return (++*str, 'H');
		return ('<');
	}
	else if (**str == '>')
	{
		if (*++*str == '>')
			return (++*str, '+');
		return ('>');
	}
	else
		return ('a');
	return (0);
}

int	get_token(char **ps, char *es, char **q, char **eq)
{
	char	*str;
	int		ret;
	bool	skip;

	skip = false;
	str = *ps;
	skip_spaces(str, es);
	if (q)
		*q = str;
	ret = *str;
	if (ft_strchr("|", *str) && *str != 0)
	{
		str++;
		skip = true;
	}
	else
		ret = sw_get_token(&str);
	while (str < es && !ft_strchr(SPACES, *str) && !ft_strchr(TOKENS, *str) \
		&& !skip && ret == 'a')
		str++;
	if (eq)
		*eq = str;
	*ps = str;
	return (ret);
}

int	get_token_a(char **ps)
{
	char	*ptr;

	ptr = *ps;
	while (*ptr)
	{
		if (ft_isalnum(*ptr) || *ptr == '_')
			ptr++;
		else
			return (-1);
	}
	return ('a');
}
