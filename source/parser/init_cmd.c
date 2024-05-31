
#include "../include/minishell.h"

// char whitespace[] = " \t\r\n\v";
// char symbols[] = "<|>&;()";

// ast_factory(&s, input)
// {

// }

t_cmd	*parse_input(char *input)
{
	// parsecmd(input);
	// void (*input)
	return (parsecmd(input));
}

// int getcmd(char *buf, int nbuf)
// {
// 	write(2, "$ ", 2);
// 	memset(buf, 0, nbuf);
// 	gets(buf, nbuf);
// 	if(buf[0] == 0) // EOF
// 		return -1;
// 	return 0;
// }

t_cmd *execcmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = EXEC;
	// return (t_cmd*)cmd;
	return (cmd);
}

t_cmd *redircmd(t_cmd *subcmd, char *file, char *efile, int mode, int fd)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = REDIR;
	cmd->cmd = subcmd;
	cmd->file = file;
	cmd->efile = efile;
	cmd->mode = mode;
	cmd->fd = fd;
	// return (t_cmd*)cmd;
	return (cmd);
}

t_cmd *pipecmd(t_cmd *left, t_cmd *right)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	// return (t_cmd*)cmd;
	return (cmd);
}

char symbols[] = "<|>&;()";

int gettoken(char **ps, char *es, char **q, char **eq)
{
	char *s;
	int ret;

	s = *ps;
	while(s < es && strchr(SPACES, *s))
		s++;
	if(q)
		*q = s;
	ret = *s;
	switch(*s){
	case 0:
		break;
	case '|':
	case '(':
	case ')':
	case ';':
	case '&':
	case '<':
		s++;
		break;
	case '>':
		s++;
		if(*s == '>'){
		ret = '+';
		s++;
		}
		break;
	default:
		ret = 'a';
		while(s < es && !strchr(SPACES, *s) && !strchr(SYMBOLS, *s))
		s++;
		break;
	}
	if(eq)
		*eq = s;

	while(s < es && strchr(SPACES, *s))
		s++;
	*ps = s;
	return ret;
}
