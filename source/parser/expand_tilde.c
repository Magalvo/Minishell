
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

char	*expand_tilde_equal(char *input, char *ps, t_ms *s)
{
	char	*res;

	if (strrchr_alpha_loop(input, ps - 1))
	{
		if (*(ps + 1) == '+')
			res = expand_tilde_pwd(input, ps, true, s);
		else if (*(ps + 1) == '-')
			res = expand_tilde_oldpwd(input, ps, true, s);
		else
			res = expand_tilde(input, ps, true, s);
	}
	if (res == input)
		return (input);
	return(free(input), res);
}

char	*expand_tilde_pwd(char *input, char *ps, bool check, t_ms *s)
{
	char	*val;
	char	*res;

	if (ft_isspace(*(ps - 1)) || ps == input || check)
	{
		val = get_env_val(s->env, "PWD", s);
		if (val != NULL)
		{
			if (ft_strchr(" :/", *(ps + 2)))
				res = get_expanded(input, ps, val, ps + 2);
			free(val);
			return(free(input), res);
		}
	}
	return (input);
}

char	*expand_tilde_oldpwd(char *input, char *ps, bool check, t_ms *s)
{
	char	*val;
	char	*res;

	if (ft_isspace(*(ps - 1)) || ps == input || check)
	{
		val = get_env_val(s->env, "OLDPWD", s);
		if (val != NULL)
		{
			if (ft_strchr(" :/", *(ps + 2)))
				res = get_expanded(input, ps, val, ps + 2);
			free(val);
			return(free(input), res);
		}
	}
	return (input);
}

char	*expand_tilde(char *input, char *ps, bool check, t_ms *s)
{
	char	*val;
	char	*res;

	if (ft_isspace(*(ps - 1)) || ps == input || check)
	{
		val = get_env_val(s->env, "HOME", s);
		if (val != NULL)
		{
			if (ft_strchr(" :/", *(ps + 1)))
				res = get_expanded(input, ps, val, ps + 2);
			free(val);
			return(free(input), res);
		}
	}
	return (input);
}

/*
char	*expand_tilde(char *input, char *ps, t_ms *s)
{
	char	*key;
	char	*val;
	char	*res;
	// char	*end;

	if (*(ps + 1) == '+')
		key = "PWD";
	else if (*(ps + 1) == '-')
		key = "OLDPWD";
	else
		key = "HOME";
	val = get_env_val(s->env, key, s);
	if (val != NULL)
	{
		if ((*(ps + 1) == '+') || (*(ps + 1) == '-'))
			res = get_expanded(input, ps, val, ps + 2);
		else
			res = get_expanded(input, ps, val, ps + 1);
		free(val);
		return(free(input), res);
	}
	return (input);
}
*/

bool	strrchr_alpha_loop(const char *input, const char *pos)
{
	pos--;
	if (!ft_isalpha(*pos))
		return (false);
	while (*pos < *input)
	{
		if (ft_isalpha(*pos))
			pos--;
		else if (ft_isspace(*pos))
			return (true);
		else
			return (false);
	}
	return (false);
}
