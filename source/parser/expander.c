
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
	Tilde Expansion ~    ~+    ~-
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

char	*expander(char *input, t_ms *s)
{
	char *start;
	char *end;
	char *expand;
	char *expanded;

	start = ft_strnstr(input, "$", ft_strlen(input));
	if (start && !inside_quotes(input, start))
	{
		end = start;
		// end++;
		while (ft_isalpha(*++end) || *end == '_')
			;
		expand = ft_substr(input, start - input, end - start);
		expanded = get_env_val(s->env, expand, s);
		if (expanded == NULL)
			expanded = expand;
		printf("expand: %s\n", expand);
		printf("expanded: %s\n", expanded);
	}

/*
	find = ft_strnstr(input, "=", ft_strlen(input));
		if (find && find++ = '~' && find++ = '/') // =~/
			find = ft_strnstr(input, "~", ft_strlen(input));


	find = ft_strnstr(input, "~+", ft_strlen(input));
	if (find && !inside_quotes(input, find))
		replace

	find = ft_strnstr(input, "~-", ft_strlen(input));
	find = ft_strnstr(input, "~", ft_strlen(input));


	find = ft_strnstr(input, ">(", ft_strlen(input));
	if (find && !inside_quotes(input, find))
	{
		end = ft_strchr(find, ')');
		if (!inside_quotes(input, end))
			glue_str(find, end);
	}
	*/

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
