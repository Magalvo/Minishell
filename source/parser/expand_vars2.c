
#include "../include/minishell.h"

char	*expand_dolar_loop(char *input, t_ms *s)
{
	char	*start;
	// char	*end;
	// char	*key;
	char	*res;

	start = ft_strnstr(input, "$", ft_strlen(input));
	while (start != NULL && (*(char *)start + 1 != '?' && *(char *)start + 1 != '0' &&
		!ft_strchr(SPACES, *(char *)(start + 1))))
	{
		if (start && !chr_betw(input, start, '\''))
		{
			res = expand_dolar(input, start, s);
			// end = start;
			// while (ft_isalpha(*++end) || *end == '_')
			// 	;
			// key = ft_substr(input, start - input, end - start);
			// res = get_expanded(input, start, get_env_val(s->env, key, s), /*\*/
			// 		start + (ft_strlen(key)));
			// free (key);
			// free (input);
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
	int		keylen;

	end = ps;
	keylen = 0;
	while (ft_isalpha(*++end) || *end == '_')
		;
	key = ft_substr(input, (ps + 1) - input, (end - 1) - ps);
	if (key)
		keylen = (ft_strlen(key)) + 1;
	res = get_expanded(input, ps, get_env_val(s->env, key, s), \
			ps + keylen);
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
	char	*first_qt;
	char	*last_qt;
	char	*res1;
	char	*res2;
	bool	is_qt;

	
	first_qt = get_first_quote(input);
	if (!first_qt)
		return (input);
	if (*first_qt == QUOTE)
		is_qt = true;
	else if (*first_qt == DQUOTE)
		is_qt = false;

	res1 = get_expanded(input, first_qt, NULL, first_qt + 1);
	free(input);
	if (is_qt)
		last_qt = ft_strchr(res1, QUOTE);
	else
		last_qt = ft_strchr(res1, DQUOTE);
	res2 = get_expanded(res1, last_qt, NULL, last_qt + 1);
	free(res1);
	return (res2);
}
