/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:15:46 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/06/27 14:01:44 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
ABOUT PARAMETERS NAMES
char *input becomes **ptr_input (&input), so parsing position can be passed
char *end is pointer to end of input: end = input + ft_strlen(input);
char *q		is pointer to start of quote
char *eq	is pointer to end of quote
*/

t_cmd	*parse_input(char *input, t_ms *s)
{
	char	*xp_input;
	t_cmd	*ast;

	if (ft_strlen(input) == 0)
		return (NULL);
	add_history(input);
	if (!syntax_validation(input, s))
		return (NULL);
	xp_input = ft_strdup(input);
	xp_input = expand_sw_vars(xp_input, s);
	xp_input = expand_sw_tilde(xp_input, s);
	xp_input = expand_sw_quotes(xp_input);
	ast = parse_cmd(xp_input, s);
	free(xp_input);
	xp_input = NULL;
	return (ast);
}

t_cmd *parse_cmd(char *input, t_ms *s)
{
	char	*end;
	t_cmd	*cmd;

	if (input == NULL)
		return (NULL);
	end = input + ft_strlen(input);
	cmd = parse_line(&input, end, s);

	peek(&input, end, "");
	if(input != end){
		ft_dprintf(STDERR_FILENO, "\'%s\' ", input);
		reprompt(INCOMPLETE_PARSE, 1, s);
	}
	return cmd;
}

// ps is pointer to a position of input
// end is a pointer to the end of the symbol
// so ptr_cmd	end_cmd
t_cmd *parse_line(char **ps, char *es, t_ms *s)
{
	t_cmd *cmd;

	cmd = parse_pipe(ps, es, s);
	// while(peek(ps, es, "&")){
	// 	get_token(ps, es, 0, 0);
	// 	cmd = backcmd(cmd);
	// }
	// if(peek(ps, es, ";")){
	// 	get_token(ps, es, 0, 0);
	// 	cmd = listcmd(cmd, parse_line(ps, es));
	// }
	return cmd;
}

// looks for pipes, if found runs recursively until no pipe found
t_cmd *parse_pipe(char **ps, char *es, t_ms *s)
{
	t_cmd *cmd;

 	cmd = parse_exec(ps, es, s);
	if(peek(ps, es, "|")){
		get_token(ps, es, 0, 0);
		cmd = cmd_pipe(cmd, parse_pipe(ps, es, s));
	}
	return cmd;
}

// < infile, open O_RDONLY
// > outfile, open O_WRONLY|O_CREAT|O_TRUNC
// H heredoc, open O_WRONLY|O_CREAT, no truncate
// + >>, open O_WRONLY|O_CREAT|O_APPEND
t_cmd *parse_redir(t_cmd *cmd, char **ps, char *es, t_ms *s)
{
	int		tok;
	char	*q;
	char	*eq;

	while(peek(ps, es, "<>"))
	{
		tok = get_token(ps, es, 0, 0);
		if(get_token(ps, es, &q, &eq) != 'a')
			reprompt(MISSING_REDIRECT, 1, s);
		// make_filename(q, eq);
		// cmd = redir_sw(cmd, tok, q, eq);
		cmd = redir_sw(cmd, tok, ft_substr(q, 0, eq - q), s);
		// ft_substr(q, 0, eq - q);

	}
	return (cmd);
}

// t_cmd *redir_sw(t_cmd *cmd, int tok, char *file, char *efile)
t_cmd *redir_sw(t_cmd *cmd, int tok, char *filename, t_ms *s)
{
	// char	*filename;

	// filename = ft_substr(file, 0, efile - file);
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
