
#include "../include/minishell.h"

void	split_input(t_ms *s, char* input)
{
	s->cmd_temp = ft_split(input, ' ');
}

int	add_slash(char *slash, char **paths)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (paths[i])
	{
		len = ft_strlen(paths[i]);
		if (paths[i][len - 1] != '/')
		{
			slash = ft_strjoin(paths[i], "/");
			if (!slash)
				return (free_paths(paths, i), 0);
			free(paths[i]);
			paths[i] = slash;
		}
		i++;
	}
	return (1);
}

void	panic(char *s)
{
	fprintf(stderr, "%s\n", s);
	// exit(1);
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
	t_exec *ecmd;
	t_pipe *pcmd;
	t_redir *rcmd;

	if(cmd == 0)
		return 0;

	switch(cmd->type){
	case EXEC:
		ecmd = (t_exec*)cmd;
		for(i=0; ecmd->argv[i]; i++)
		*ecmd->eargv[i] = 0;
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
