/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_newstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:12:16 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/08/16 21:01:19 by cjoao-de         ###   ########.fr       */
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
	char	*expanded;
	size_t	first;
	size_t	insert;
	size_t	last;

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

// shrinks input string by the diference of input prt and move ptr
void	get_shrinked(char *input, char *move)
{
	size_t	move_len;

	(void)input;
	move_len = ft_strlen(move);
	ft_memmove(move, move + 1, move_len);
}

void	str_rm_char(char *input, char remove)
{
	char	*ptr;

	while (true)
	{
		ptr = ft_strchr(input, remove);
		if (!ptr)
			break ;
		get_shrinked(input, ptr);
	}
}
