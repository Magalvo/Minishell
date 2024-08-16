/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prechecks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:15:00 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/08/16 19:58:01 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// preparse syntax validation, rejects invalid symbols and crude syntax errors
bool	syntax_validation(char *input, t_ms *s)
{
	if (!syntax_quotes(input))
		return (reprompt(MISSING_QUOTE, 1, s), NULL);
	if (!syntax_and_or(input))
		return (reprompt(LOGICAL_TOKEN, 1, s), NULL);
	if (!syntax_pipes(input, (char *)input + ft_strlen(input)))
		return (reprompt(PIPE_SYNTAX, 2, s), NULL);
	if (!syntax_list(input))
		return (reprompt(SEMICOLON, 1, s), NULL);
	if (!syntax_back(input))
		return (reprompt(SINGLE_AMPERSAND, 1, s), NULL);
	if (!syntax_parenthesis(input))
		return (reprompt(PARENTHESIS, 1, s), NULL);
	if (!syntax_redir(input, (char *)input + ft_strlen(input)))
		return (reprompt(INVALID_TOKEN, 2, s), NULL);
	else
		return (true);
}

// iterates char *input to find $VAR possible to expand, returns expanded string
char	*expand_sw_vars(char *input, t_ms *s)
{
	char	*pos;
	char	*xp_input;

	xp_input = ft_strdup(input);
	pos = ft_strchr(xp_input, '$');
	while (pos)
	{
		if (is_quoted(xp_input, pos) != E_QUOTE)
		{
			if ((pos > xp_input && *(pos - 1) == '"' && *(pos + 1) == '"')
				|| (pos != NULL && ft_strchr(SPACES, *(pos + 1))))
				*(pos) = DOLAR;
			pos = ft_strchr(xp_input, '$');
			xp_input = vars_sw(xp_input, pos, s);
			if (s->error == true)
				break ;
			pos = ft_strchr(xp_input, '$');
		}
		else
			pos = ft_strchr(pos + 1, '$');
	}
	free(input);
	return (xp_input);
}

char	*tilde_sw(char *xp_input, char *pos, t_ms *s)
{
	if (ft_strnstr(xp_input, "=~", ft_strlen(xp_input)))
		xp_input = expand_tilde_equal(xp_input, pos, s);
	if (ft_strnstr(xp_input, "~+", ft_strlen(xp_input)))
		xp_input = expand_tilde_pwd(xp_input, pos, false, s);
	else if (ft_strnstr(xp_input, "~-", ft_strlen(xp_input)))
		xp_input = expand_tilde_oldpwd(xp_input, pos, false, s);
	else
		xp_input = expand_tilde(xp_input, pos, false, s);
	return (xp_input);
}

char	*expand_sw_tilde(char *input, t_ms *s)
{
	char	*pos;
	char	*xp_input;

	xp_input = ft_strdup(input);
	pos = ft_strchr(xp_input, '~');
	while (pos)
	{
		if (is_quoted(xp_input, pos) == NONE)
		{
			xp_input = tilde_sw(xp_input, pos, s);
		}
		if (ft_strchr(xp_input, '~') == pos)
			pos = ft_strchr(pos + 1, '~');
		else
			pos = ft_strchr(xp_input, '~');
	}
	return (free(input), xp_input);
}

char	*expand_sw_quotes(char *input)
{
	char	*pos;
	char	*end;

	pos = NULL;
	pos = get_first_quote(input);
	end = NULL;
	while (pos != NULL)
	{
		if (*pos == QUOTE)
			end = ft_strchr(pos + 1, '\'');
		else if (*pos == DQUOTE)
			end = ft_strchr(pos + 1, '"');
		glue_str(pos, end);
		unquoter(pos + 1, end);
		pos = get_first_quote(end + 1);
	}
	return (input);
}

/* char	*expand_sw_quotes(char *input)
{
	char	*pos;
	char	*end;

	pos = NULL;
	pos = get_first_quote(input);
	end = NULL;
	while (pos != NULL)
	{
		if (*pos == QUOTE)
		{
			end = ft_strchr(pos + 1, '\'');
			glue_str(pos, end);
			unquoter(pos + 1, end);
		}
		else if (*pos == DQUOTE)
		{
			end = ft_strchr(pos + 1, '"');
			glue_str(pos, end);
			unquoter(pos + 1, end);
		}
		pos = get_first_quote(end + 1);
	}
	return (input);
} */

// char	*expand_sw_tilde(char *input, t_ms *s)
// {
// 	char	*pos;
// 	char	*xp_input;

// 	xp_input = ft_strdup(input);
// 	pos = ft_strchr(xp_input, '~');
// 	while (pos)
// 	{
// 		if (is_quoted(xp_input, pos) == NONE)
// 		{
// 			if (ft_strnstr(xp_input, "=~", ft_strlen(xp_input)))
// 				xp_input = expand_tilde_equal(xp_input, pos, s);
// 			if (ft_strnstr(xp_input, "~+", ft_strlen(xp_input)))
// 				xp_input = expand_tilde_pwd(xp_input, pos, false, s);
// 			else if (ft_strnstr(xp_input, "~-", ft_strlen(xp_input)))
// 				xp_input = expand_tilde_oldpwd(xp_input, pos, false, s);
// 			else
// 				xp_input = expand_tilde(xp_input, pos, false, s);
// 		}
// 		if (ft_strchr(xp_input, '~') == pos)
// 			pos = ft_strchr(pos + 1, '~');
// 		else
// 			pos = ft_strchr(xp_input, '~');
// 	}

// 	return (free(input), xp_input);
// }
