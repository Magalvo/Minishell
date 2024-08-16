/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:15:46 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/08/16 19:49:51 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// < infile, open O_RDONLY
// > outfile, open O_WRONLY|O_CREAT|O_TRUNC
// H heredoc, open O_WRONLY|O_CREAT, no truncate
// + >>, open O_WRONLY|O_CREAT|O_APPEND
t_cmd	*parse_redir(t_cmd *cmd, char **ps, char *es, t_ms *s)
{
	int		tok;
	char	*q;
	char	*eq;
	char	*filename;

	eq = NULL;
	q = NULL;
	while (peek(ps, es, "<>"))
	{
		tok = get_token(ps, es, 0, 0);
		if (peek(ps, es, TOKENS))
		{
			return (free_ast2(&cmd), reprompt(INVALID_TOKEN, 2, s), NULL);
		}
		if (get_token(ps, es, &q, &eq) != 'a')
		{
			return (free_ast2(&cmd), reprompt(MISSING_REDIRECT, 2, s), NULL);
		}
		filename = ft_substr(q, 0, eq - q);
		cmd = redir_sw(cmd, tok, filename, s);
	}
	return (cmd);
}

t_cmd	*redir_sw(t_cmd *cmd, int tok, char *filename, t_ms *s)
{
	if (tok == '<')
		cmd = cmd_redir_in(cmd, filename, O_RDONLY, s);
	else if (tok == '>')
		cmd = cmd_redir_out(cmd, filename, O_WRONLY | O_CREAT | O_TRUNC, s);
	else if (tok == '+')
		cmd = cmd_redir_out(cmd, filename, O_WRONLY | O_CREAT | O_APPEND, s);
	else if (tok == 'H')
		cmd = cmd_heredoc(cmd, filename, O_RDWR | O_CREAT | O_APPEND, s);
	return (cmd);
}

void	parse_fake_redir(char **ps, char *es, t_ms *s)
{
	int		tok;
	char	*q;
	char	*eq;

	(void)s;
	while (peek(ps, es, "<>"))
	{
		tok = get_token(ps, es, 0, 0);
		if (peek(ps, es, TOKENS))
		{
			while (peek(ps, es, TOKENS))
				get_token(ps, es, 0, 0);
			return ;
		}
		if (get_token(ps, es, &q, &eq) != 'a')
			return ;
	}
	(void)tok;
	return ;
}
