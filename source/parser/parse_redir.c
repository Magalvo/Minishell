/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:15:46 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/03 16:47:49 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// < infile, open O_RDONLY
// > outfile, open O_WRONLY|O_CREAT|O_TRUNC
// H heredoc, open O_WRONLY|O_CREAT, no truncate
// + >>, open O_WRONLY|O_CREAT|O_APPEND
t_cmd *parse_redir(t_cmd *cmd, char **ps, char *es, t_ms *s)
{
	int		tok;
	char	*q;
	char	*eq;

	eq = NULL;
	q = NULL;
	while(peek(ps, es, "<>"))
	{
		tok = get_token(ps, es, 0, 0);
		if (peek(ps, es, TOKENS))
		{
			reprompt(INVALID_TOKEN, 1, s);
			while (peek(ps, es, TOKENS))
				get_token(ps, es, 0, 0);
			return (NULL);
		}
		// if(get_token(ps, es, &q, &eq) != 'a' && !s->one_dolar)
		if(get_token(ps, es, &q, &eq) != 'a')
		{
			free(cmd);
			return (reprompt(MISSING_REDIRECT, 1, s), NULL);
		}	
		// {
			// reprompt(MISSING_REDIRECT, 1, s);
		// }
		// else if(get_token(ps, es, &q, &eq) != 'a' && s->one_dolar)
		// 	cmd = redir_sw(cmd, tok, "$", s);
		// {
		// }
		cmd = redir_sw(cmd, tok, ft_substr(q, 0, eq - q), s);
	}
	return (cmd);
}

// t_cmd *redir_sw(t_cmd *cmd, int tok, char *file, char *efile)
t_cmd *redir_sw(t_cmd *cmd, int tok, char *filename, t_ms *s)
{
	if (tok == '<')
		cmd = cmd_redir(cmd, filename, O_RDONLY, 0);
	else if (tok == '>')
		cmd = cmd_redir(cmd, filename, O_WRONLY|O_CREAT|O_TRUNC, 1);
	else if (tok == '+')		// ? (+) is (>>)
		cmd = cmd_redir(cmd, filename, O_WRONLY|O_CREAT|O_APPEND, 1);
	else if (tok == 'H') // todo check flags: (H) is here_doc
		cmd = cmd_heredoc(cmd, filename, O_RDWR|O_CREAT|O_APPEND, s);
	return (cmd);
}

void	parse_fake_redir(char **ps, char *es, t_ms *s)
{
	int		tok;
	char	*q;
	char	*eq;

	while(peek(ps, es, "<>"))
	{
		tok = get_token(ps, es, 0, 0);
		if (peek(ps, es, TOKENS))
		{
			reprompt(INVALID_TOKEN, 1, s);
			while (peek(ps, es, TOKENS))
				get_token(ps, es, 0, 0);
			return ;
		}
		if(get_token(ps, es, &q, &eq) != 'a')
			return ;
	}
	(void)tok;
	return ;
}
