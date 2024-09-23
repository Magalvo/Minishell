/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:12:16 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/09/19 16:13:30 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	untokenizer(char *start, char *end)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(TOKENS))
	{
		ft_strrep_range(start, end, TOKENS[i], UNTOKENS[i]);
		i++;
	}
}

void	retokenizer(char *start, char *end)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(TOKENS))
	{
		ft_strrep_range(start, end, UNTOKENS[i], TOKENS[i]);
		i++;
	}
}

void	unquoter(char *start, char *end)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(QUOTES))
	{
		ft_strrep_range(start, end, QUOTES[i], UNQUOTES[i]);
		i++;
	}
}

void	requoter(char *start, char *end)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(QUOTES))
	{
		ft_strrep_range(start, end, UNQUOTES[i], QUOTES[i]);
		i++;
	}
}

void	get_endstr_ptr(char **str)
{
	if (!str)
		return ;
	while (**str != '\0')
		(*str)++;
}
