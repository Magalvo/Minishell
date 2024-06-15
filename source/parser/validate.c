
#include "../include/minishell.h"

bool	syntax_validation(char *input)
{

// TODO	syntax_validation(input);
	// TODO brutally check syntax errors, missing checks:
	// invalid chars (#^@)
	// TODO recheck flow, where to exit? on reprompt? need t_ms s for that
	// TODO check if they are inside quotes / dquotes?
	// ! ALL THESE CHECKS FAIL IF INSIDE quotes
	// ? run > between_char(char *input, char *totest, char tofind)
	// ? EXPAND BEFORE OR AFTER PARSING?
	// forbidden expressions
	// >(	<(   ${

	// char *find;
	// char *end;

	// find = ft_strnstr(input, ">(", ft_strlen(input))
	// if (!inside_quotes(input, find))
	// {
	// 	end = ft_strchr(find)
	// 	if (!inside_quotes(input, end))
	// 		glue_str(find, end)
	// }

	// if (ft_strcount(input, '\'') != 0)


	if (ft_strcount(input, '\'') % 2 != 0)
		return(reprompt(MISSING_QUOTE), NULL);

	else if (ft_strcount(input, '"') % 2 != 0)
		return(reprompt(MISSING_QUOTE), NULL);
	else if (ft_strchr(input, ';') != 0)
		return(reprompt(SEMICOLON), NULL);

	else if (ft_strcount(input, '(') || ft_strcount(input, ')'))
		return(reprompt(PARENTHESIS), NULL);
	// else if (ft_strcount(input, '(') != ft_strcount(input, ')'))
	// 	return(reprompt(BLOCK_MISSING), NULL);

	else if (ft_strnstr(input, "||", ft_strlen(input)))
		return(reprompt(INVALID_TOKEN), NULL);

	else if (ft_strnstr(input, "&&", ft_strlen(input)))
		return(reprompt(INVALID_TOKEN), NULL);
	else
		return (true);
}
