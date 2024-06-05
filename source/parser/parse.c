
#include "../include/minishell.h"

t_cmd	*parse_input(char *input)
{
	if (ft_strlen(input) == 0)
		return (NULL);

	// parse_cmd(input);
	// void (*input)
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
		ft_dprintf(STDERR_FILENO, "leftovers: %s\n", input);
		panic("syntax");
	}
	// nulterminate(cmd);
	return cmd;
}

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

t_cmd *parse_redir(t_cmd *cmd, char **ps, char *es)
{
	int tok;
	char *q, *eq;

	while(peek(ps, es, "<>")){
		tok = gettoken(ps, es, 0, 0);
		if(gettoken(ps, es, &q, &eq) != 'a')
		panic("missing file for redirection");
		switch(tok){
		case '<':
		cmd = cmd_redir(cmd, q, eq, O_RDONLY, 0);
		break;
		case '>':
		cmd = cmd_redir(cmd, q, eq, O_WRONLY|O_CREAT|O_TRUNC, 1);
		break;
		case '+':  // >>
		cmd = cmd_redir(cmd, q, eq, O_WRONLY|O_CREAT, 1);
		break;
		}
	}
	return cmd;
}

t_cmd *parse_block(char **ps, char *es)
{
	t_cmd *cmd;

	if(!peek(ps, es, "("))
		panic("parse_block");
	gettoken(ps, es, 0, 0);
	cmd = parse_line(ps, es);
	if(!peek(ps, es, ")"))
		panic("syntax - missing )");
	gettoken(ps, es, 0, 0);
	cmd = parse_redir(cmd, ps, es);
	return cmd;
}
