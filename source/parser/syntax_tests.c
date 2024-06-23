
#include "../include/minishell.h"

bool	syntax_pipes(const char *str, const char *end)
{
	while(str && ft_strchr(SPACES, *str))
		str++;
	if (ft_strchr("|", *str))
		return (false);
	while(str < end && ft_strrchr(SPACES, *end))
		end--;
	if (ft_strrchr("|", *end))
		return (false);
	return (true);
}

bool	syntax_and_or(const char *str)
{
	char	*pos;

	pos = ft_strchr(str, '|');
	if (pos && ft_strchr(pos + 1, '|') && syntax_quoted(str, pos) == NONE)
		return (false);
	pos = ft_strchr(str, '&');
	if (pos && ft_strchr(pos + 1, '&') && syntax_quoted(str, pos) == NONE)
		return (false);
	return (true);
}

bool	syntax_list(const char *str)
{
	char	*pos;

	pos = ft_strchr(str, ';');
	if (pos && syntax_quoted(str, pos) == NONE)
		return (false);
	return (true);
}

bool	syntax_back(const char *str)
{
	char	*pos;

	pos = ft_strchr(str, '&');
	if (pos && syntax_quoted(str, pos) == NONE)
		return (false);
	return (true);
}
