/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:09:13 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/30 19:02:39 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// TODO check if inside {} is 0 ? _
char	*expand_curly(char *input, char *ps, t_ms *s)
{
	char	*res;
	char	*key;
	char	*end;
	char	*val;

	end = ft_strchr(ps, '}');
	key = ft_substr(input, ps - input + 2, end - ps - 2);
	if (get_token_a(&key) == 'a')
	{
		val = get_env_val(s->env, key, s);
		res = get_expanded(input, ps, val, end + 1);
		free2(key, val);
		return (free(input), res);
	}
	return (reprompt(CURLY_ERROR, 1, s), NULL);
}

char	*expand_pid(char *input, char *ps, t_ms *s)
{
	char	*pid;
	char	*res;

	(void)s;
	pid = ft_getpid();
	if (get_token_a(&pid) == 'a')
	{
		res = get_expanded(input, ps, pid, ps + 2);
		free(pid);
		return (free(input), res);
	}
	return (reprompt(GETPID_ERROR, 1, s), NULL);
}

char	*expand_exit_stat(char *input, char *ps, t_ms *s)
{
	char	*stat;
	char	*res;

	stat = ft_itoa(s->exit_stat);
	if (get_token_a(&stat) == 'a')
	{
		res = get_expanded(input, ps, stat, ps + 2);
		free(stat);
		return (free(input), res);
	}
	return (reprompt(EXPANSION_ERROR, 1, s), NULL);
}

char	*expand_last_cmd(char *input, char *ps, t_ms *s)
{
	char	*val;
	char	*res;
	char	*key;

	key = ft_strdup("_");
	val = get_env_val(s->env, key, s);
	res = get_expanded(input, ps, val, ps + 2);
	free2(key, val);
	return (free(input), res);
}

char	*expand_self(char *input, char *ps, t_ms *s)
{
	char	*val;
	char	*res;

	val = get_env_val(s->env, "SHELL", s);
	if (!val)
		val = "minishell";
	res = get_expanded(input, ps, val, ps + 2);
	free(val);
	return (free(input), res);
}
