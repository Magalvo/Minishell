
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

	// else if (ft_strcount(input, '(') || ft_strcount(input, ')'))
	// 	return(reprompt(PARENTHESIS), NULL);
	// else if (ft_strcount(input, '(') != ft_strcount(input, ')'))
	// 	return(reprompt(BLOCK_MISSING), NULL);
	else
		return (true);
}




// Helper function to check if a character is escaped
bool is_escaped(const char *str, const char *pos) {
	bool escaped = false;
	while (pos > str && *(pos - 1) == '\\') {
		escaped = !escaped;
		pos--;
	}
	return escaped;
}
