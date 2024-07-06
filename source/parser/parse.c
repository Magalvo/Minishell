/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:15:46 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/05 19:33:15 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
ABOUT PARAMETERS NAMES
char *input becomes **ps (&input), so parsing position can be passed
char *es is pointer to end of input: end = input + ft_strlen(input);
char *q		is pointer to start of symbol
char *eq	is pointer to end of symbol
*/

t_cmd	*parse_input(char *input, t_ms *s)
{
	char	*xp_input;
	t_cmd	*ast;

	if (ft_strlen(input) == 0)
		return (NULL);
	add_history(input);
	s->input = input;
	if (!syntax_validation(input, s))
		return (NULL);
	xp_input = ft_strdup(input);
	// xp_input = expand_sw_vars(xp_input, s);
	if (xp_input == NULL)
		return (NULL);
	xp_input = expand_sw_tilde(xp_input, s);
	if (xp_input == NULL)
		return (NULL);
	xp_input = expand_sw_quotes(xp_input);
	if (xp_input == NULL)
		return (NULL);
	ast = parse_cmd(xp_input, s);
	free(xp_input);
	xp_input = NULL;
	return (ast);
}

t_cmd	*parse_cmd(char *input, t_ms *s)
{
	char	*end;
	t_cmd	*cmd;
	char	*quote;

	if (input == NULL)
		return (NULL);
	ft_strrep_range(input, NULL, (char)17, '$');
	end = NULL;
	end = input;
	while (true)
	{
		quote = get_first_quote(end);
		if (quote == NULL)
			break ;
		end = ft_strchr(quote + 1, *quote);
		untokenizer(quote, end);
		end = ft_strchr(end + 1, *quote);
	}
	end = input + ft_strlen(input);
	cmd = parse_pipe(&input, end, s);
	peek(&input, end, "");
	if (input != end)
	{
		ft_dprintf(STDERR_FILENO, "\'%s\' ", input);
		reprompt(INCOMPLETE_PARSE, 2, s);
	}
	return (cmd);
}

// looks for pipes, if found runs recursively until no pipe found
t_cmd	*parse_pipe(char **ps, char *es, t_ms *s)
{
	t_cmd	*cmd;

	cmd = parse_exec(ps, es, s);
	if (cmd != NULL && peek(ps, es, "|"))
	{
		get_token(ps, es, 0, 0);
		cmd = cmd_pipe(cmd, parse_pipe(ps, es, s));
	}
	return (cmd);
}
