
#include "../include/minishell.h"

/*
control operator
A token that performs a control function.
It is a newline or one of the following:
'||', '&&', '&', ';', ';;', ';&', ';;&', '|', '|&', '(', or ')'.

metacharacter
A character that, when unquoted, separates words.
A metacharacter is a space, tab, newline, or one of the following characters:
'|', '&', ';', '(', ')', '<', or '>'.
*/

/*
https://www.gnu.org/software/bash/manual/html_node/Shell-Expansions.html
	// Brace Expansion -> dont implement except
	expand -> ${parameter} only		// ! maybe
	Tilde Expansion ~
	https://www.gnu.org/software/bash/manual/html_node/Tilde-Expansion.html
	Shell Parameter Expansion -> dont interpret -> {}
	Command Substitution -> dont implement -> $(command)
	Arithmetic Expansion -> dont implement -> $(( expression ))
	Process Substitution -> dont implement -> <(list) >(list)  :named pipes
	 Word Splitting
	https://www.gnu.org/software/bash/manual/html_node/Word-Splitting.html
	// Filename Expansion -> dont implement
    Quote Removal
*/

char	*expander(char *input)
{
	return(input);
	char	*expanded_input;
	char	*braces;
	char	*tilde;
	char	*words;
	// char	*quotes;

	syntax_validation(input);
	braces = expand_braces(input);
	tilde = expand_tilde(braces);
	free(braces);
	words = expand_words(tilde);
	free(tilde);
	expanded_input = remove_quotes(words);
	free(words);
	return (expanded_input);
}


char	*expand_braces(char *input)
{
	if ((ft_strcount(input, '{') && ft_strcount(input, '}')) &&
		(ft_strcount(input, '{') == ft_strcount(input, '}')))
	{
		return ("a");
	}
	return ("a");
}

char	*expand_tilde(char *input)
{
	char	*expanded;
	char	*tilde_ptr;

	tilde_ptr = ft_strnstr(input, "~", ft_strlen(input));
	expanded = tilde_ptr;
/*
	if (tilde_ptr && !ft_strnstr(tilde_ptr, "~", ft_strlen(input)))
		strcpy until ~
		strjoin ~expansion
		strjoin after ~
		expanded
	else if (ft_strnstr(tilde_ptr, "~"))
		// peek ????
	else
		expanded = ft_strdup(input); //make something to free after
*/
	return (expanded);
}

char	*expand_words(char *input)
{
	return (input);
}
char	*remove_quotes(char *input)
{
	return (input);
}
