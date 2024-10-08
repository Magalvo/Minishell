/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:15:46 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/09/30 17:05:15 by dde-maga         ###   ########.fr       */
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

t_cmd	*parse_input(char **input, t_ms *s)
{
	char	*xp_input;
	t_cmd	*ast;

	if (ft_strlen(*input) == 0)
		return (NULL);
	add_history(*input);
	s->input = *input;
	if (!syntax_validation(*input, s))
		return (NULL);
	xp_input = ft_strdup(*input);
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
	end = NULL;
	end = input;
	while (true)
	{
		quote = get_first_quote(end);
		if (quote == NULL)
			break ;
		end = ft_strchr(quote + 1, *quote);
		untokenizer(quote, end);
		// end = ft_strchr(end + 1, *quote);
		if (*end != '\0')
			end++;
	}
	end = input + ft_strlen(input);
	cmd = parse_pipe(&input, end, s);
	peek(&input, end, "");
	return (cmd);
}

// looks for pipes, if found runs recursively until no pipe found
t_cmd	*parse_pipe(char **ps, char *es, t_ms *s)
{
	t_cmd	*cmd;
	t_cmd	*dcmd;

	cmd = parse_exec(ps, es, s);
	cmd_info(cmd, 0);
	if (cmd != NULL && peek(ps, es, "|"))
	{
		get_token(ps, es, 0, 0);
		dcmd = parse_pipe(ps, es, s);
		cmd = cmd_pipe(cmd, dcmd, s);
	}
	return (cmd);
}
