
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

	// ! glue quotes
	// ! glue dquotes
	// ? expand dolar
	// ! expand tilde
	// ! glue quotes
	// ! glue dquotes
	// ! parse_ast && //remove quotes

char	*expand_dolar(char *input, t_ms *s)
{
	char	*start;
	char	*end;
	char	*key;
	char	*res;

	start = ft_strnstr(input, "$", ft_strlen(input));
	while (start != NULL && (*(char *)start + 1 != '?' && *(char *)start + 1 != '0' &&
		!ft_strchr(SPACES, *(char *)(start + 1))))
	{
		if (start && !chr_betw(input, start, '\''))
		{
			end = start;
			while (ft_isalpha(*++end) || *end == '_')
				;
			key = ft_substr(input, start - input, end - start);
			res = get_expanded(input, start, get_env_val(s->env, key, s), \
					start + (ft_strlen(key)));
			free (key);
			free (input);
			input = res;
		}
		start = ft_strnstr(input, "$", ft_strlen(input));
	}
	res = ft_strdup(input);
	return(free(input), res);
}

// due to limitations of subject. expansion in the form: ~username are not done
// ~ expansion are optional, we choose to do them for PWD, OLDPWD, HOME
/*
char	*expand_tilde(char *input, t_ms *s)
{
	char *start;
	char *end;
	char *expand;
	char *expanded;
	char *expansion;

	// ~+/
	// ~-/
	// ~/

	// :~
	// =~
	// ~

	start = ft_strnstr(input, ":~", ft_strlen(input));
	start = ft_strnstr(input, "=~", ft_strlen(input));
	start = ft_strnstr(input, "~", ft_strlen(input));
	while (start != NULL)
	{
		if (start && !inside_quotes(input, start))
		{
			end = start;
			if (ft_strchr("=", start -1) ||
				ft_strchr(":", start - 1) || start == input) // start at index [0]
			{
				if (ft_strchr("/", start + 1) && *s != 0)
			}
			if (start + 1 != '-')
			// end++;
			while (ft_isalpha(*++end) || *end == '_')
				;
			expand = ft_substr(input, start - input, end - start);
			expansion = get_env_val(s->env, expand, s);
			if (expansion != NULL)
			{
				expanded = get_expanded(input, start, expansion, start + (ft_strlen(expand)));
			// free something around here
				input = expanded;
			}
			else
				return (input);
		}
		start = ft_strnstr(input, "$", ft_strlen(input));
	}
	return(input);
}
*/

// nip_tuck_input: creates new input *char replacing with expanded parts
char	*get_expanded(char *input, char *cut, char *paste, char *remain)
{
	// echo $PWD $LIXO $USER $LLL
	char *expanded;
	int first;
	int insert;
	int last;

	first = cut - input;	//size of right string
	insert = ft_strlen(paste);	//size of insert string
	last = ft_strlen(remain);
	expanded = ft_calloc(1, first + insert + last);
	ft_memmove(expanded, input, first);
	ft_memmove(expanded + first, paste, insert);
	ft_memmove(expanded + first + insert, remain, last);
	return (expanded);
}

// ! delete me, maybe
char	*expand_braces(char *input)
{
	if ((ft_strcount(input, '{') && ft_strcount(input, '}')) &&
		(ft_strcount(input, '{') == ft_strcount(input, '}')))
	{
		return ("a");
	}
	return ("a");
}

// stub
char	*expand_words(char *input)
{
	return (input);
}
// TODO this
char	*remove_quotes(char *input)
{
	return (input);
}
