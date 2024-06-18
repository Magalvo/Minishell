
#include "../include/minishell.h"

// ? OLD PARSER WITH BONUS STUBS
/*
ABOUT PARAMETERS NAMES
char *input becomes **ptr_input (&input), so parsing position can be passed
char *end is pointer to end of input: end = input + ft_strlen(input);
char *q
char *eq
*/

t_cmd	*parse_input(char *input, t_ms *s)
{
	char	*xp_input;
	t_cmd	*ast;
	// char	*ppid;

	if (ft_strlen(input) == 0)
		return (NULL);
	xp_input = ft_strdup(input);
	xp_input = expand_dolar(xp_input, s);
	// glue_str(input, NULL);
	// unglue_str(input, NULL);
	ast = parse_cmd(xp_input);
	// ? should expanded_input be free() or pointed to _ (last command)
	// free(expanded_input);
	// ppid = ft_getpid();
	// printf("%s\n", ppid);
	// ppid = ft_getrnd_str();
	// printf("%s\n", ppid);
	return (ast);
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
	// 	get_token(ps, es, 0, 0);
	// 	cmd = backcmd(cmd);
	// }
	// if(peek(ps, es, ";")){
	// 	get_token(ps, es, 0, 0);
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
		get_token(ps, es, 0, 0);
		cmd = cmd_pipe(cmd, parse_pipe(ps, es));
	}
	return cmd;
}

// < infile, open O_RDONLY
// > outfile, open O_WRONLY|O_CREAT|O_TRUNC
// H heredoc, open O_WRONLY|O_CREAT, no truncate
// + >>, open O_WRONLY|O_CREAT|O_APPEND
t_cmd *parse_redir(t_cmd *cmd, char **ps, char *es)
{
	int		tok;
	char	*q;
	char	*eq;

	while(peek(ps, es, "<>"))
	{
		tok = get_token(ps, es, 0, 0);
		if(get_token(ps, es, &q, &eq) != 'a')
			reprompt(MISSING_REDIRECT);
		cmd = redir_sw(cmd, tok, q, eq);
		// if (tok == '<')
		// 	cmd = cmd_redir(cmd, q, eq, O_RDONLY, 0);
		// else if (tok == '>')
		// 	cmd = cmd_redir(cmd, q, eq, O_WRONLY|O_CREAT|O_TRUNC, 1);
		// else if (tok == '+')		// ? (+) is (>>)
		// 	cmd = cmd_redir(cmd, q, eq, O_WRONLY|O_CREAT|O_APPEND, 1);
		// else if (tok == 'H') // todo check flags: (H) is here_doc
		// 	cmd = cmd_heredoc(cmd, filename2, O_RDWR|O_CREAT|O_APPEND);
	}
	return (cmd);
}

t_cmd *redir_sw(t_cmd *cmd, int tok, char *file, char *efile)
{
	char	*filename;

	filename = ft_substr(file, 0, file - efile);
	if (tok == '<')
			cmd = cmd_redir(cmd, filename, O_RDONLY, 0);
	else if (tok == '>')
		cmd = cmd_redir(cmd, filename, O_WRONLY|O_CREAT|O_TRUNC, 1);
	else if (tok == '+')		// ? (+) is (>>)
		cmd = cmd_redir(cmd, filename, O_WRONLY|O_CREAT|O_APPEND, 1);
	else if (tok == 'H') // todo check flags: (H) is here_doc
		cmd = cmd_heredoc(cmd, filename, O_RDWR|O_CREAT|O_APPEND);
	return (cmd);

}


t_cmd *parse_block(char **ps, char *es)
{
	t_cmd *cmd;

	if(!peek(ps, es, "("))
		reprompt(BLOCK_WTF);
	get_token(ps, es, 0, 0);
	cmd = parse_line(ps, es);
	if(!peek(ps, es, ")"))
		reprompt(BLOCK_UNCLOSED);
	get_token(ps, es, 0, 0);
	cmd = parse_redir(cmd, ps, es);
	return cmd;
}
