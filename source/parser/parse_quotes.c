
#include "../include/minishell.h"


/*
Enclosing characters in single quotes (') preserves the literal value
of each character within the quotes.
A single quote may not occur between single quotes,
even when preceded by a backslash.

Enclosing characters in double quotes (") preserves the literal value
of all characters within the quotes, with the exception of ($), ('), (\).
The characters ($) and (') retain their special meaning within double quotes.
The backslash retains its special meaning only when followed
by one of the following characters: ($), ('), ("), (\), or newline (\n).
Within double quotes, backslashes that are followed
by one of these characters are removed
*/

// enum s_quote_type { NONE 0, EQUOTE 1, EDQUOTE 2 };
// # define QUOTE '		DQUOTE "
// key[0] unused, key[1] for quote, key[2] for dquote
// TODO too many lines // implement the XOR ^= trick here
int syntax_quotes(const char *str)
{
	int key[3] = {NONE, NONE, NONE};

	while (*str)
	{
		if (*str == QUOTE)
		{
			if (key[EDQUOTE] == NONE)
			{
				if (key[EQUOTE] == NONE)	// implement the XOR ^= trick here
					key[EQUOTE] = EQUOTE;
				else
					key[EQUOTE] = NONE;
			}
		}
		else if (*str == DQUOTE)
		{
			if (key[EQUOTE] == NONE)
			{
				if (key[EDQUOTE] == NONE)
					key[EDQUOTE] = EDQUOTE;
				else
					key[EDQUOTE] = NONE;
			}
		}
		str++;
	}
	if (key[EQUOTE] != NONE || key[EDQUOTE] != NONE)
		return (-1);
	return (0);
}

// check what type of quotes a ptr on a string has, if any
int is_quoted(const char *str, const char *totest)
{
	int quote;

	quote = NONE;
	if (totest == NULL)
		return (-1);
	while (str < totest)
	{

		if (*str == QUOTE)
		{
			if (quote == NONE)
				quote = EQUOTE;
			else if (quote == EQUOTE)
				quote = NONE;
		}
		else if (*str == DQUOTE)
		{
			if (quote == NONE)
				quote = EDQUOTE;
			else if (quote == EDQUOTE)
				quote = NONE;
		}
	str++;
	}
	return (quote);
}

/*
//' "' 1 '" "'1'" '
  | "1" "1" |
'		0
"		1
last	"

	bool to_xpnd


	'"$VAR"' "'$goleft"'

	int ' 1
	int " 1
	char last '
	  ^				- totest
*/

// tests if pointer has char on sides of its position
bool	chr_betw(char *input, char *totest, char tofind)
{
	char *goleft;
	char *goright;

	goleft = totest;
	goright = totest;
	if (ft_strchr(input, tofind) < goleft)
	{
		if (ft_strrchr(input, tofind) > goright)
		return (true);		// char found on both sides
	}
	return (false);

	// while (goright != input || *goright != '\0') //hmm, test is stupid!?!
	// {
	// 	if (ft_strchr(goleft, tofind) && ft_strrchr(goright, tofind))
	// 		return (true);		// char found on both sides

	// }
	// return (false);
}

// tests if quotes, dquotes exists on both sides of pointer
bool	inside_quotes(char *input, char *totest)
{
	char quote;
	char dquote;

	quote = '\'';
	dquote = '"';
	if (chr_betw(input, totest, quote) || chr_betw(input, totest, dquote))
		return (true);		// char found on both sides
	return (false);
}

// does nothing for now
bool	check_valid_position(char *input)
{

	char *ptr;

	ptr = ft_strchr(input, ')');
	if (inside_quotes(input, ptr))
		return true;
	return false;
}

// char *find_first(char *input, char c)
// {
// 	char	*ptr;

// 	ptr = ft_strchr(input, c);
// 	if (ptr)
// 	{
// 		if (ft_strchr(ptr, c) < ptr)
// 		{
// 			ptr = ft_strchr(ptr, c);
// 		}
// 	}


// }
