
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

/* int peek(char **ps, char *es, char *toks)
{
	char *s;

	s = *ps;
	while(s < es && strchr(whitespace, *s))
		s++;
	*ps = s;
	return *s && strchr(toks, *s);
} */

// NUL-terminate all the counted strings.
/* struct cmd *nulterminate(struct cmd *cmd)
{
	int i;
	struct execcmd *ecmd;
	struct pipecmd *pcmd;
	struct redircmd *rcmd;

	if(cmd == 0)
		return 0;

	switch(cmd->type){
	case EXEC:
		ecmd = (struct execcmd*)cmd;
		for(i=0; ecmd->argv[i]; i++)
		*ecmd->eargv[i] = 0;
		break;

	case REDIR:
		rcmd = (struct redircmd*)cmd;
		nulterminate(rcmd->cmd);
		*rcmd->efile = 0;
		break;

	case PIPE:
		pcmd = (struct pipecmd*)cmd;
		nulterminate(pcmd->left);
		nulterminate(pcmd->right);
		break;
	}
	return cmd;
} */
