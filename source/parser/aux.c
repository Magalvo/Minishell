
#include "../include/minishell.h"

void	split_input(t_ms *s, char* input)
{
	s->cmd_temp = ft_split(input, ' ');
}

int peek(char **ps, char *es, char *toks)
{
	char *s;

	s = *ps;
	while(s < es && strchr(SPACES, *s))
		s++;
	*ps = s;
	return *s && strchr(toks, *s);
}

// NUL-terminate all the counted strings.
t_cmd *nulterminate(t_cmd *cmd)
{
	int i;
	struct t_exec *ecmd;
	struct t_pipe *pcmd;
	struct t_redir *rcmd;

	if(cmd == 0)
		return 0;

	switch(cmd->type){
	case EXEC:
		ecmd = (struct t_exec*)cmd;
		for(i=0; ecmd->argv[i]; i++)
		*ecmd->eargv[i] = 0;
		break;

	case REDIR:
		rcmd = (struct t_redir*)cmd;
		nulterminate(rcmd->cmd);
		*rcmd->efile = 0;
		break;

	case PIPE:
		pcmd = (struct t_pipe*)cmd;
		nulterminate(pcmd->left);
		nulterminate(pcmd->right);
		break;
	}
	return cmd;
}
