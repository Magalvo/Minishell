
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

int syntax_quotes(const char *str)
{
	int key[3] = {NONE, NONE, NONE}; // key[0] unused, key[1] for single quote, key[2] for double quote

	while (*str)
	{
		if (*str == QUOTE)
		{
			if (key[2] == NONE)
			{
				if (key[1] == NONE) // If single quote is not active
					key[1] = EQUOTE; // Mark as active
				else // If single quote is active
					key[1] = NONE; // Mark as closed
			}
		}
		else if (*str == DQUOTE)
		{
			if (key[1] == NONE)
			{
				if (key[2] == NONE) // If double quote is not active
					key[2] = EDQUOTE; // Mark as active
				else // If double quote is active
					key[2] = NONE; // Mark as closed
			}
		}
		str++;
	}
	if (key[1] != NONE || key[2] != NONE)
		return -1; // Indicate an unclosed quote block
	else
		return 0; // All quotes are closed
}

// Main function to determine the quote context of a character in a string
int syntax_quoted(const char *str, const char *totest)
{
	int state;

	state = NONE;
	if (totest == NULL)
		return (-1);
	// for (const totest *p = str; p < pos; ++p) {
	while (str < totest)
	{

		if (*str == QUOTE)
		{
			if (state == NONE)
				state = EQUOTE;
			else if (state == EQUOTE)
				state = NONE;
		}
		else if (*str == DQUOTE)
		{
			if (state == NONE)
				state = EDQUOTE;
			else if (state == EDQUOTE)
				state = NONE;
		}
	str++;
	}
	return (state);
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
