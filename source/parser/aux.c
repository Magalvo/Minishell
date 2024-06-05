
#include "../include/minishell.h"

void	split_input(t_ms *s, char* input)
{
	/* if (s->cmd_temp)
		ft_free_dptr(&s->cmd_temp); */
	s->cmd_temp = ft_split(input, ' ');
}

void	panic(char *s)
{
	ft_dprintf(STDERR_FILENO, "%s\n", s);
	// exit(1);
}

int peek(char **ps, char *es, char *toks)
{
	char *s;

	s = *ps;
	while(s < es && ft_strchr(SPACES, *s))
		s++;
	*ps = s;
	return *s && ft_strchr(toks, *s);
}

// NUL-terminate all the counted strings.
t_cmd *nulterminate(t_cmd *cmd)
{
	// int i;
	// t_exec *ecmd;
	t_pipe *pcmd;
	t_redir *rcmd;

	if(cmd == 0)
		return 0;

	switch(cmd->type){
	case EXEC:
		// ecmd = (t_exec*)cmd;
		// for(i=0; ecmd->argv[i]; i++)
		// *ecmd->eargv[i] = 0;
		break;

	case REDIR:
		rcmd = (t_redir*)cmd;
		nulterminate(rcmd->cmd);
		*rcmd->efile = 0;
		break;

	case PIPE:
		pcmd = (t_pipe*)cmd;
		nulterminate(pcmd->left);
		nulterminate(pcmd->right);
		break;
	}
	return cmd;
}
