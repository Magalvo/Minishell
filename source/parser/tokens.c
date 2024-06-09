
#include "../include/minishell.h"

int	sw_get_token(char **str)
{
	if (!**str)
		return (0);
	else if (**str == '&')
	{
		if (*++*str == '&')
			return (str++, 'N');
	}
	else if (**str == '<')
	{
		if (*++*str == '<')
			return (str++, 'H');
		return ('<');
	}
	else if (**str == '>')
	{
		if (*++*str == '>')
			return (str++, '+');
		return ('>');
	}
	else
		return ('a');
	return (0);
}

int get_token(char **ps, char *es, char **q, char **eq)
{
	char *s;
	int ret;

	s = *ps;
	while(s < es && ft_strchr(SPACES, *s))
		s++;
	if(q)
		*q = s;
	ret = *s;
	if (ft_strchr("|()", *s) && *s != 0)
		s++;
	else
		ret = sw_get_token(&s);
	while(s < es && !ft_strchr(SPACES, *s) && !ft_strchr(SYMBOLS, *s))
		s++;
	if(eq)
		*eq = s;
	while(s < es && ft_strchr(SPACES, *s))
		s++;
	*ps = s;
	return (ret);
}

// get token backup
/*
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
	// case '&': // add & for AND
	case '&':
		s++;
		if(*s == '&')
		{
			ret = 'N';
			s++;
		}
		break;
	// case '<':
	// 	s++;
	// 	break;
	case '<':
		s++;
		if(*s == '<'){
			ret = 'H';
			s++;
		}
		break;
	case '>':
		s++;
		if(*s == '>')
		{
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
*/
