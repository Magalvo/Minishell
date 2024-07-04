/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:17:00 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/04 23:28:02 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	syntax_pipes(const char *str, const char *end)
{
	while (str < end && ft_strchr(SPACES, *str))
		str++;
	if (str == end)
		return (true);
	if (ft_strchr("|", *str))
		return (false);
	while (str < end && ft_strrchr(SPACES, *end - 1))
		end--;
	if (ft_strrchr("|", *(end - 1)))
		return (false);
	return (true);
}
// < g.sh wc |
bool	syntax_and_or(const char *str)
{
	char	*pos;

	pos = ft_strchr(str, '|');
	while (pos && *(pos + 1) != '\0')
	{
		if (ft_strchr("|", *(pos + 1)) && is_quoted(str, pos) == NONE)
			return (false);
		pos = ft_strchr(pos + 1, '|');
	}
	pos = ft_strchr(str, '&');
	while (pos && *(pos + 1) != '\0')
	{
		if (ft_strchr("&", *(pos + 1)) && is_quoted(str, pos) == NONE)
			return (false);
		pos = ft_strchr(pos + 1, '&');
	}
	return (true);
}

bool	syntax_list(const char *str)
{
	char	*pos;

	pos = ft_strchr(str, ';');
	if (pos && is_quoted(str, pos) == NONE)
		return (false);
	return (true);
}

bool	syntax_back(const char *str)
{
	char	*pos;

	pos = ft_strchr(str, '&');
	if (pos && is_quoted(str, pos) == NONE)
		return (false);
	return (true);
}

bool	syntax_parenthesis(const char *str)
{
	char	*pos;

	pos = ft_strchr(str, '(');
	if (pos && is_quoted(str, pos) == NONE)
		return (false);
	pos = ft_strchr(str, ')');
	if (pos && is_quoted(str, pos) == NONE)
		return (false);
	return (true);
}
