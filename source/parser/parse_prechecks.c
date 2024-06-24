
#include "../include/minishell.h"

bool	syntax_validation(char *input, t_ms *s)
{
	if (syntax_quotes(input))
		return(reprompt(MISSING_QUOTE, 1, s), NULL);
	if (!syntax_and_or(input))
		return(reprompt(LOGICAL_TOKEN, 1, s), NULL);
	if (!syntax_pipes(input, (char *)input + ft_strlen(input) - 1))
		return(reprompt(PIPE_SYNTAX, 2, s), NULL);
	if (!syntax_list(input))
		return(reprompt(SEMICOLON, 1, s), NULL);
	if (!syntax_back(input))
		return(reprompt(SINGLE_AMPERSAND, 1, s), NULL);
	if (!syntax_parenthesis(input))
		return(reprompt(PARENTHESIS, 1, s), NULL);
	else
		return (true);
}

char	*expand_sw_vars(char *input, t_ms *s)
{
	char	*pos;
	char	*xp_input;

	xp_input = ft_strdup(input);
	pos = ft_strchr(xp_input, '$');
	while (pos && *(pos + 1) != '\0')
	{
		if (is_quoted(xp_input, pos) != EQUOTE)
		{
			if (*(pos + 1) == '{')
				xp_input = expand_curly(xp_input, pos, s);
			else if (*(pos + 1) == '$')
				xp_input = expand_pid(xp_input, pos, s);
			else if (*(pos + 1) == '?')
				xp_input = expand_exit_stat(xp_input, pos, s);
			else if (*(pos + 1) == '_')
				xp_input = expand_last_cmd(xp_input, pos, s);
			else if (*(pos + 1) == '0')
				xp_input = expand_self(xp_input, pos, s);
			else
				xp_input = expand_dolar(xp_input, pos, s);
		}
		if (xp_input == NULL)
			break ;			// TODO proper exit condition
		pos = ft_strchr(xp_input, '$');
	}
	return(free(input), xp_input);
}

char	*expand_sw_tilde(char *input, t_ms *s)
{
	char	*pos;
	char	*xp_input;

	xp_input = ft_strdup(input);
	pos = ft_strchr(xp_input, '~');
	while (pos)
	{
		if (is_quoted(xp_input, pos) == NONE)
		{
			if (ft_strnstr(input, "=~", ft_strlen(input)))
				xp_input = expand_tilde_equal(xp_input, pos, s);
			if (ft_strnstr(input, "~+", ft_strlen(input)))
				xp_input = expand_tilde_pwd(xp_input, pos, false, s);
			else if (ft_strnstr(input, "~-", ft_strlen(input)))
				xp_input = expand_tilde_oldpwd(xp_input, pos, false, s);
			else
				xp_input = expand_tilde(xp_input, pos, false, s);
		}
		pos = ft_strchr(pos, '~');
		}
	return(free(input), xp_input);
}
