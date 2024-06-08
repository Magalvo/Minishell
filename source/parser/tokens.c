
#include "../include/minishell.h"

// char whitespace[] = " \t\r\n\v";
// char symbols[] = "<|>&;()";

int gettoken(char **ps, char *es, char **q, char **eq)
{
	char *s;
	int ret;

	s = *ps;
	while(s < es && ft_strchr(SPACES, *s))
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
	// case ';':
	case '&': // add & for AND
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
	// TODO add << check for heredoc
	default:
		ret = 'a';
		while(s < es && !ft_strchr(SPACES, *s) && !ft_strchr(SYMBOLS, *s))
		s++;
		break;
	}
	if(eq)
		*eq = s;

	while(s < es && ft_strchr(SPACES, *s))
		s++;
	*ps = s;
	return ret;
}
