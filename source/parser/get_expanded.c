/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_expanded.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:12:16 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/06/26 17:12:33 by cjoao-de         ###   ########.fr       */
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

// due to limitations of subject. expansion in the form: ~username are not done
// ~ expansion is optional, we choose to do them for PWD, OLDPWD, HOME

// nip_tuck_input: creates new input *char replacing with expanded parts
char	*get_expanded(char *input, char *cut, char *paste, char *remain)
{
	char *expanded;
	size_t first;
	size_t insert;
	size_t last;

	first = ft_strlen(input) - ft_strlen(cut);
	if (paste == NULL)
		insert = 0;
	else
		insert = ft_strlen(paste);
	last = ft_strlen(remain);
	expanded = ft_calloc(1, first + insert + last + 1);
	ft_memcpy(expanded, input, first);
	ft_memcpy(expanded + first, paste, insert);
	ft_memcpy(expanded + first + insert, remain, last);
	return (expanded);
}

/* STRING MAGIC STARTS HERE */

// replaces -search- with -replace- on the range between *start and *end
// if end is NULL, searches until end of string.
void	ft_strrep_range(char *start, char *end, char search, char replace)
{
	char *ptr;

	if (start == NULL)
		return ;
	ptr = start;
	if (end == NULL)
	{
		while (*ptr != '\0')
		{
			if (*ptr == search)
				*ptr = replace;
			ptr++;
		}
	}
	else
	{
		while (ptr != end)
		{
			if (*ptr == search)
				*ptr = replace;
			ptr++;
		}
	}
}

void	glue_str(char *start, char *end)
{
	size_t i;

	i = 0;
	while (i < ft_strlen(SPACES))
	{
		ft_strrep_range(start, end, SPACES[i], GLUE[i]);
		i++;
	}
}

void	unglue_str(char *start, char *end)
{
	size_t i;

	i = 0;
	while (i < ft_strlen(SPACES))
	{
		ft_strrep_range(start, end, GLUE[i], SPACES[i]);
		i++;
	}
}
