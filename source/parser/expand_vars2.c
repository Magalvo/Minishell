
#include "../include/minishell.h"

char	*expand_dolar_loop(char *input, t_ms *s)
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

char	*expand_dolar(char *input, char *ps, t_ms *s)
{
	char	*end;
	char	*key;
	char	*res;

	end = ps;
	while (ft_isalpha(*++end) || *end == '_')
		;
	key = ft_substr(input, ps - input, end - ps);
	res = get_expanded(input, ps, get_env_val(s->env, key, s), \
			ps + (ft_strlen(key)));
	free (key);
	return(free(input), res);
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
