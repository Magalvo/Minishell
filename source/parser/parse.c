
#include "../include/minishell.h"

t_cmd	*parse_input(char *input)
{
	// parsecmd(input);
	// void (*input)
	return (parsecmd(input));
}

t_cmd *parsecmd(char *input)
{
	char	*end;
	t_cmd	*cmd;

	end = input + ft_strlen(input);
	cmd = parseline(&input, end);
	peek(&input, end, "");
	if(input != end){
		fprintf(stderr, "leftovers: %s\n", input);
		panic("syntax");
	}
	nulterminate(cmd);
	return cmd;
}

t_cmd *parseline(char **ps, char *es)
{
	t_cmd *cmd;

	cmd = parsepipe(ps, es);
	// while(peek(ps, es, "&")){
	// 	gettoken(ps, es, 0, 0);
	// 	cmd = backcmd(cmd);
	// }
	// if(peek(ps, es, ";")){
	// 	gettoken(ps, es, 0, 0);
	// 	cmd = listcmd(cmd, parseline(ps, es));
	// }
	return cmd;
}
t_cmd *parsepipe(char **ps, char *es)
{
	t_cmd *cmd;

	cmd = parseexec(ps, es);
	if(peek(ps, es, "|")){
		gettoken(ps, es, 0, 0);
		cmd = pipecmd(cmd, parsepipe(ps, es));
	}
	return cmd;
}

t_cmd *parseredirs(t_cmd *cmd, char **ps, char *es)
{
	int tok;
	char *q, *eq;

	while(peek(ps, es, "<>")){
		tok = gettoken(ps, es, 0, 0);
		if(gettoken(ps, es, &q, &eq) != 'a')
		panic("missing file for redirection");
		switch(tok){
		case '<':
		cmd = redircmd(cmd, q, eq, O_RDONLY, 0);
		break;
		case '>':
		cmd = redircmd(cmd, q, eq, O_WRONLY|O_CREAT|O_TRUNC, 1);
		break;
		case '+':  // >>
		cmd = redircmd(cmd, q, eq, O_WRONLY|O_CREAT, 1);
		break;
		}
	}
	return cmd;
}

t_cmd *parseblock(char **ps, char *es)
{
	t_cmd *cmd;

	if(!peek(ps, es, "("))
		panic("parseblock");
	gettoken(ps, es, 0, 0);
	cmd = parseline(ps, es);
	if(!peek(ps, es, ")"))
		panic("syntax - missing )");
	gettoken(ps, es, 0, 0);
	cmd = parseredirs(cmd, ps, es);
	return cmd;
}

t_cmd *parseexec(char **ps, char *es)
{
	char *q, *eq;
	int tok, argc;
	t_cmd *cmd;
	t_cmd *ret;
	char	**_argv;

	if(peek(ps, es, "("))
		return parseblock(ps, es);

	ret = execcmd();
	cmd = (t_cmd*)ret;

	argc = 0;
	ret = parseredirs(ret, ps, es);
	char *ps_cpy = *ps;
	char *es_cpy = es;
	while(!peek(ps, es, "|)&;"))
	{
		if((tok=gettoken(ps, es, &q, &eq)) == 0)
			break;
		if(tok != 'a')
			panic("syntax");
		argc++;
	}
	_argv = create_argv(argc);
	// (void)_argv;
	*ps = ps_cpy;
	es = es_cpy;
	argc = 0;
	char *new_arg;
	while(!peek(ps, es, "|)&;"))
	{
		if((tok=gettoken(ps, es, &q, &eq)) == 0)
			break;
		if(tok != 'a')
			panic("syntax");

		// _argv[argc] = (malloc(sizeof(char *) * (q - eq))		;
		new_arg = calloc(sizeof(char), (eq - q));
		// char *new_arg = malloc(sizeof(char) * (eq - q + 1));
		// char *new_arg = malloc(sizeof(char) * (3));
		// ft_strlcpy(new_arg, q, (eq - q + 1));
		ft_memmove((char *)new_arg, (char *)q, (eq - q));
		_argv[argc] = new_arg;
		cmd->argv[argc] = q;
		cmd->eargv[argc] = eq;
		argc++;
		////////////////
		///////////////
		if(argc >= MAXARGS)
			panic("too many args");
		ret = parseredirs(ret, ps, es);
	}
	cmd->argv[argc] = 0;
	cmd->eargv[argc] = 0;
	cmd->temp = _argv;
	return ret;
}

char **create_argv(int nbr)
{
	char **arr;

	arr = (char **)malloc(sizeof(char *) * (nbr + 1));
	// ft_bzero(arr, (sizeof(char *) * (nbr + 1)));
	// cmd = malloc(sizeof(*cmd));
	// ft_memset(arr, (sizeof(char *) * (nbr)));
	return(arr);
	// return((char **)malloc(sizeof(char *) * (nbr)));
}

void create_arg( char **argv, char *str)
{
	while (*argv)
		argv++;
	*argv = str;
}
