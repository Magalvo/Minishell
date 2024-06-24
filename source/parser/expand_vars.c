
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

char	*expand_curly(char *input, char *ps, t_ms *s)
{
	// char	*start;
	char	*res;
	char	*key;
	char	*end;
	(void)s;

	end = ft_strchr(ps, '}');
	key = ft_substr(input, ps - input + 2, end - ps - 2);
	if (get_token_a(&key) == 'a')
	{
		res = get_expanded(input, ps, get_env_val(s->env, key, s), \
					end + 1);
		free(key);
		return(free(input), res);
	}
	return(reprompt(EXPANSION_ERROR), NULL);
}

char	*expand_pid(char *input, char *ps, t_ms *s)
{
	(void)s;
	char	*pid;
	char	*res;

	pid = ft_getpid();
	if (get_token_a(&pid) == 'a')
	{
		res = get_expanded(input, ps, pid, ps + 2);
		free(pid);
		return(free(input), res);
	}
	return(reprompt(GETPID_ERROR), NULL);
}

char	*expand_exit_stat(char *input, t_ms *s)
{
	(void)s;
	return(input);
}

char	*expand_last_cmd(char *input, t_ms *s)
{
	(void)s;
	return(input);
}

char	*expand_self(char *input, t_ms *s)
{
	(void)s;
	return(input);
}




// stub
char	*expand_words(char *input)
{
	return (input);
}
// TODO this
char	*remove_quotes(char *input)
{
	// char 17
	return (input);
}
