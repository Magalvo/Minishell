/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prechecks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:15:00 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/03 16:51:32 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	syntax_validation(char *input, t_ms *s)
{
	if (syntax_quotes(input))
		return(reprompt(MISSING_QUOTE, 1, s), NULL);
	if (!syntax_and_or(input))
		return(reprompt(LOGICAL_TOKEN, 1, s), NULL);
	if (!syntax_pipes(input, (char *)input + ft_strlen(input)))
		return(reprompt(PIPE_SYNTAX, 2, s), NULL);
	if (!syntax_list(input))
		return(reprompt(SEMICOLON, 1, s), NULL);
	if (!syntax_back(input))
		return(reprompt(SINGLE_AMPERSAND, 1, s), NULL);
	if (!syntax_parenthesis(input))
		return(reprompt(PARENTHESIS, 1, s), NULL);
	else
		return (true);
}

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
			// if (*(pos + 1) == '{')	//}
			// 	xp_input = expand_curly(xp_input, pos, s);
			// else if (*(pos + 1) == '$')
			// 	xp_input = expand_pid(xp_input, pos, s);
			// else if (*(pos + 1) == '?')
			// 	xp_input = expand_exit_stat(xp_input, pos, s);
			// else if (*(pos + 1) == '_')
			// 	xp_input = expand_last_cmd(xp_input, pos, s);
			// else if (*(pos + 1) == '0')
			// 	xp_input = expand_self(xp_input, pos, s);
			// else
			// 	xp_input = expand_dolar(xp_input, pos, s);
			xp_input = vars_sw(xp_input, pos, s);
			pos = ft_strchr(xp_input, '$');
			if (pos && *(pos - 1) == '"' && *(pos + 1) == '"')
				*(pos) = 17;
		}
		else
			pos = ft_strchr(pos + 1, '$');
	}
	return(free(input), xp_input);
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
			if (ft_strnstr(input, "=~", ft_strlen(input)))
				xp_input = expand_tilde_equal(xp_input, pos, s);
			if (ft_strnstr(input, "~+", ft_strlen(input)))
				xp_input = expand_tilde_pwd(xp_input, pos, false, s);
			else if (ft_strnstr(input, "~-", ft_strlen(input)))
				xp_input = expand_tilde_oldpwd(xp_input, pos, false, s);
			else
				xp_input = expand_tilde(xp_input, pos, false, s);
		}
		pos = ft_strchr(pos + 1, '~');
		}
	return(free(input), xp_input);
}

char	*expand_sw_quotes(char *input)
{
	char	*pos;
	char	*end;

	pos = NULL;
	pos = get_first_quote(input);
	while (pos != NULL)
	{
		if (*pos == QUOTE)
		{
			end = ft_strchr(pos + 1, '\'');
			glue_str(pos, end);
		}
		else if (*pos == DQUOTE)
		{
			end = ft_strchr(pos + 1, '"');
			glue_str(pos, end);
		}
		pos = get_first_quote(end + 1);
	}
	return (input);
}
