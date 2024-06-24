
#include "../include/minishell.h"

void	reset_ms()
{
	// todo
	// new_line();
	// free stuff
	// back to prompt
}

void	reprompt(char *s)
{
	ft_dprintf(STDERR_FILENO, "%s\n", s);
	reset_ms();
}

// looks ahead of the string to find *tokens while skipping spaces
int peek(char **ps, char *es, char *tokens)
{
	char *s;

	s = *ps;
	while(s < es && ft_strchr(SPACES, *s))
		s++;
	*ps = s;
	return *s && ft_strchr(tokens, *s);
}

// looks ahead of the string to find *tokens while skipping spaces
int peek_nsp(char **ps, char *es, char *tokens)
{
	char *s;

	s = *ps;
	while(s < es && ft_strchr(SPACES, *s))
		s++;
	*ps = s;
	return *s && ft_strchr(tokens, *s);
}

// Helper function to check if a character is escaped
/*
bool is_escaped(const char *str, const char *pos) {
	bool escaped = false;
	while (pos > str && *(pos - 1) == '\\') {
		escaped = !escaped;
		pos--;
	}
	return escaped;
}
*/


// // NUL-terminate all the counted strings.
// t_cmd *nulterminate(t_cmd *cmd)
// {
// 	// int i;
// 	// t_exec *ecmd;
// 	t_pipe *pcmd;
// 	t_redir *rcmd;

// 	if(cmd == 0)
// 		return 0;

// 	switch(cmd->type){
// 	case EXEC:
// 		// ecmd = (t_exec*)cmd;
// 		// for(i=0; ecmd->argv[i]; i++)
// 		// *ecmd->eargv[i] = 0;
// 		break;

// 	case REDIR:
// 		rcmd = (t_redir*)cmd;
// 		nulterminate(rcmd->cmd);
// 		*rcmd->efile = 0;
// 		break;

// 	case PIPE:
// 		pcmd = (t_pipe*)cmd;
// 		nulterminate(pcmd->left);
// 		nulterminate(pcmd->right);
// 		break;
// 	}
// 	return cmd;
// }
