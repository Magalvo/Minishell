/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:07:37 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/05 19:13:12 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
Tilde Expansion
https://www.gnu.org/software/bash/manual/html_node/Tilde-Expansion.html

rules:
'~+' or '~-' or '~', expand to diferent things
must be followed by (' ', ':', '/')
if preceded by '=' is an assignment, must follow: isalpha() > = > ~(+-)
everything else should not expand
*/

// validate expansion on assign (VAR=~)
char	*expand_tilde_equal(char *input, char *ps, t_ms *s)
{
	char	*res;

	res = NULL;
	if (strrchr_alpha_loop(input, ps - 1))
	{
		if (*(ps + 1) == '+')
			res = expand_tilde_pwd(input, ps, true, s);
		else if (*(ps + 1) == '-')
			res = expand_tilde_oldpwd(input, ps, true, s);
		else
			res = expand_tilde(input, ps, true, s);
	}
	if (res == input)
		return (input);
	return (free(input), res);
}

// expands ~+ to PWD
char	*expand_tilde_pwd(char *input, char *ps, bool check, t_ms *s)
{
	char	*val;
	char	*res;

	res = NULL;
	if (ft_isspace(*(ps - 1)) || ps == input || check)
	{
		if (ft_strchr(" :/", *(ps + 2)))
		{
			val = get_env_val(s->env, "PWD", s);
			if (val != NULL)
			{
				res = get_expanded(input, ps, val, ps + 2);
				free(val);
				return (res);
			}
		}
	}
	return (input);
}

// expands ~- to OLDPWD
char	*expand_tilde_oldpwd(char *input, char *ps, bool check, t_ms *s)
{
	char	*val;
	char	*res;

	res = NULL;
	if (ft_isspace(*(ps - 1)) || ps == input || check)
	{
		if (ft_strchr(" :/", *(ps + 2)))
		{
			val = get_env_val(s->env, "OLDPWD", s);
			if (val != NULL)
			{
				res = get_expanded(input, ps, val, ps + 2);
				free(val);
				return (res);
			}
		}
	}
	return (input);
}

// regular expansion
char	*expand_tilde(char *input, char *ps, bool check, t_ms *s)
{
	char	*val;
	char	*res;

	res = NULL;
	if (ft_isspace(*(ps - 1)) || ps == input || check)
	{
		if (ft_strchr(" :/", *(ps + 1)))
		{
			val = get_env_val(s->env, "HOME", s);
			if (val != NULL)
			{
				res = get_expanded(input, ps, val, ps + 1);
				free(val);
				return (res);
			}
		}
	}
	return (input);
}

bool	strrchr_alpha_loop(const char *input, const char *pos)
{
	pos--;
	if (!ft_isalpha(*pos))
		return (false);
	while (pos > input)
	{
		if (ft_isalpha(*pos) || *pos == '_')
			pos--;
		else if (ft_isspace(*pos))
			return (true);
		else
			return (false);
	}
	return (false);
}
