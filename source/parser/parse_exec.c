
#include "../include/minishell.h"

t_cmd *parse_exec(char **ps, char *es)
{
	char *q, *eq;
	int tok, argc;
	t_cmd *cmd;
	t_cmd *ret;
	char	**_argv;

	if(peek(ps, es, "("))
		return (parse_block(ps, es));
	ret = cmd_exec();
	cmd = (t_cmd*)ret;

	argc = 0;
	ret = parse_redir(ret, ps, es);
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

		// _argv[argc] = (malloc(sizeof(char)sizeof(char *) * (q - eq))		;
		// new_arg = ft_calloc(sizeof(char), sizeof(char) * (eq - q));
		new_arg = ft_calloc((eq - q) + 1, sizeof(char));
		// char *new_arg = malloc(sizeof(char) * (eq - q + 1));
		// char *new_arg = malloc(sizeof(char) * (3));
		// ft_strlcpy(new_arg, q, (eq - q + 1));
		ft_memmove((void *)new_arg, (void *)q, (eq - q));
		_argv[argc] = new_arg;
		// cmd->argv[argc] = q;
		// cmd->eargv[argc] = eq;
		argc++;
		////////////////
		// todo cleanup
		///////////////
		if(argc >= MAXARGS)
			panic("too many args");
		ret = parse_redir(ret, ps, es);
	}
	// cmd->argv[argc] = 0;
	// cmd->eargv[argc] = 0;
	// cmd->eargv[argc] = 0;
	_argv[argc] = 0;
	cmd->argv = _argv;
	cmd->argc = argc;
	return ret;
}

char **create_argv(int nbr)
{
	// char **arr;

	// arr = (char **)malloc(sizeof(char *) * (nbr + 1));
	// arr = ft_calloc(sizeof(char *), nbr + 1);
	// ft_bzero(arr, (sizeof(char *) * (nbr + 1)));
	// cmd = malloc(sizeof(*cmd));
	// ft_memset(arr, (sizeof(char *) * (nbr)));
	// return(arr);
	return (ft_calloc((nbr + 1), sizeof(char *)));

	// return((char **)malloc(sizeof(char *) * (nbr)));
}

// void create_arg( char **argv, char *str)
// {
// 	while (*argv)
// 		argv++;
// 	*argv = str;
// }
