
#include "../include/minishell.h"

bool	syntax_validation(char *input)
{
	if (syntax_quotes(input))
		return(reprompt(MISSING_QUOTE), NULL);
	if (!syntax_and_or(input))
		return(reprompt(LOGICAL_TOKEN), NULL);
	if (!syntax_pipes(input, (char *)input + ft_strlen(input) - 1))
		return(reprompt(PIPE_SYNTAX), NULL);
	if (!syntax_list(input))
		return(reprompt(SEMICOLON), NULL);
	if (!syntax_back(input))
		return(reprompt(SINGLE_AMPERSAND), NULL);
	if (!syntax_parenthesis(input))
		return(reprompt(PARENTHESIS), NULL);
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
				xp_input = expand_last_cmd(xp_input, s);
			else if (*(pos + 1) == '0')
				xp_input = expand_self(xp_input, s);
			else
				xp_input = expand_dolar(xp_input, pos, s);
		}
		if (xp_input == NULL)
			exit(-1);			// TODO proper exit condition
		pos = ft_strchr(xp_input, '$');
	}
	return(free(input), xp_input);
}

/*
// backup for reference
char	*expand_vars_bak(char *input, t_ms *s)
{
	(void)s;
	char	*pos;
	char	*xp_input;

	pos = ft_strchr(input + 1, '$');
	if (!pos)
		return(input);
	xp_input = ft_strdup(input);
		if (is_quoted(xp_input, pos) != EQUOTE)
	while (pos && *(pos + 1) != '\0')
	{

		int is_quoted(const char *str, const char *totest);
		// input = expand_braces(input, s);	// expand ${ -- bad substitition
		if (*(pos + 1) == '{')
			xp_input = expand_curly(input, s);
		// input = expand_pid(input, s);		// $$
		if (*(pos + 1) == '$')
			xp_input = expand_pid(xp_input, s);
		// //$? = ft_itoa(s->exit_stat);
		// input = expand_exit_stat(input, s); //$? = ft_itoa(s->exit_stat);
		else if (*(pos + 1) == '?')
			xp_input = expand_exit_stat(xp_input, s);

		// expand $_;
		// 	//input = expand_last(input, s); // _
		else if (*(pos + 1) == '_')
			xp_input = expand_last_cmd(xp_input, s);
		// input = expand_self(input, s);		// $0	$SHELL
		else if (*(pos + 1) == '0')
			xp_input = expand_self(xp_input, s);

		else
			xp_input = expand_dolar(xp_input, s);
		// else if (*(pos + 1) == '0')
			// xp_input = expand_dolar(xp_input, s);
		pos = ft_strchr(pos + 1, '$');
	}
	return(free(input), xp_input);
}
*/
