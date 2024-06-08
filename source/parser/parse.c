
#include "../include/minishell.h"

/*
ABOUT PARAMETERS NAMES
char *input becomes **ptr_input (&input), so parsing position can be passed
char *end is pointer to end of input: end = input + ft_strlen(input);
char *q
char *eq
*/


t_cmd	*parse_input(char *input)
{
	if (ft_strlen(input) == 0)
		return (NULL);
	// TODO brutally check syntax errors, missing checks:
	// invalid chars (#^@)
	// TODO recheck flow, where to exit? on reprompt? need t_ms s for that
	if (ft_strcount(input, '\'') % 2 != 0)
		// reprompt(MISSING_QUOTE);
		return(reprompt(MISSING_QUOTE), NULL);
	else if (ft_strcount(input, '\'') % 2 != 0)
		// reprompt(MISSING_QUOTE);
		return(reprompt(MISSING_QUOTE), NULL);
	else if (ft_strcount(input, ';') != 0)
		// reprompt(SEMICOLON);
		return(reprompt(SEMICOLON), NULL);
	else if (ft_strcount(input, '(') != ft_strcount(input, ')'))
		// reprompt(BLOCK_MISSING);
		return(reprompt(BLOCK_MISSING), NULL);
	else if (ft_strnstr(input, "||", ft_strlen(input)))
		// reprompt(INVALID_TOKEN);
		return(reprompt(INVALID_TOKEN), NULL);
	return (parse_cmd(input));
}

t_cmd *parse_cmd(char *input)
{
	char	*end;
	t_cmd	*cmd;

	end = input + ft_strlen(input);
	cmd = parse_line(&input, end);
	peek(&input, end, "");
	if(input != end){
		ft_dprintf(STDERR_FILENO, "\'%s\' ", input);
		reprompt(INCOMPLETE_PARSE);
	}
	// nulterminate(cmd);
	return cmd;
}

// ps is pointer to a position of input
// end is a pointer to the end of the symbol
// so ptr_cmd	end_cmd
t_cmd *parse_line(char **ps, char *es)
{
	t_cmd *cmd;

	cmd = parse_pipe(ps, es);
	// while(peek(ps, es, "&")){
	// 	gettoken(ps, es, 0, 0);
	// 	cmd = backcmd(cmd);
	// }
	// if(peek(ps, es, ";")){
	// 	gettoken(ps, es, 0, 0);
	// 	cmd = listcmd(cmd, parse_line(ps, es));
	// }
	return cmd;
}

//
// looks for pipes, if found runs recursively until no pipe found
t_cmd *parse_pipe(char **ps, char *es)
{
	t_cmd *cmd;

 	cmd = parse_exec(ps, es);
	if(peek(ps, es, "|")){
		gettoken(ps, es, 0, 0);
		cmd = cmd_pipe(cmd, parse_pipe(ps, es));
	}
	return cmd;
}

// < infile, open O_RDONLY
// > outfile, open O_WRONLY|O_CREAT|O_TRUNC
// + heredoc, open O_WRONLY|O_CREAT, no truncate
// APPEND no case defined yet, not needed per subject, symbol is >|
t_cmd *parse_redir(t_cmd *cmd, char **ps, char *es)
{
	int tok;
	char *q;
	char *eq;

	while(peek(ps, es, "<>"))
	{
		tok = gettoken(ps, es, 0, 0);
		if(gettoken(ps, es, &q, &eq) != 'a')
			reprompt(MISSING_REDIRECT);
		if (tok == '<')
			cmd = cmd_redir(cmd, q, eq, O_RDONLY, 0);
		else if (tok == '>')
			cmd = cmd_redir(cmd, q, eq, O_WRONLY|O_CREAT|O_TRUNC, 1);
		else if (tok == '+')
			cmd = cmd_redir(cmd, q, eq, O_WRONLY|O_CREAT, 1);
		// TODO implement >| ? overwrite ?
	}
	return (cmd);
}

t_cmd *parse_block(char **ps, char *es)
{
	t_cmd *cmd;

	if(!peek(ps, es, "("))
		reprompt(BLOCK_WTF);
	gettoken(ps, es, 0, 0);
	cmd = parse_line(ps, es);
	if(!peek(ps, es, ")"))
		reprompt(BLOCK_UNCLOSED);
	gettoken(ps, es, 0, 0);
	cmd = parse_redir(cmd, ps, es);
	return cmd;
}
