/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:07:04 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/09/04 12:10:43 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	reprompt(char *msg, int exit_stat, t_ms *s)
{
	s->error = true;
	ft_dprintf(STDERR_FILENO, "%s\n", msg);
	s->exit_stat = exit_stat;
}

// looks ahead of the string to find *tokens while skipping spaces
int	peek(char **ps, char *es, char *tokens)
{
	char	*s;

	s = *ps;
	while (s < es && ft_strchr(SPACES, *s))
		s++;
	*ps = s;
	return (*s && ft_strchr(tokens, *s));
}

// looks ahead of the string to find spaces
int	peek_nsp(const char *ps, char *es, char *tokens)
{
	while (ps < es && !ft_strchr(SPACES, *ps))
		ps++;
	return (*ps && ft_strchr(tokens, *ps));
}

char	**create_dptr(int nbr)
{
	return (ft_calloc((nbr + 1), sizeof(char *)));
}

int	isvar(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '_');
}
