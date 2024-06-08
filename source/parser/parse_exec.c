
#include "../include/minishell.h"

// checks input for tokens and calls appropiate function
// returns a 2d_arr with the found symbols
// TODO break in 2 or 3 - so many lines ;(
t_cmd *parse_exec(char **ps, char *es)
{
	char	*q;
	char	*eq;
	int		tok;
	int		argc;
	t_cmd	*cmd;
	t_cmd	*ret;
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
			reprompt(INVALID_TOKEN);
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
			reprompt(INVALID_TOKEN);

		new_arg = ft_calloc((eq - q) + 1, sizeof(char));
		ft_memmove((void *)new_arg, (void *)q, (eq - q));
		_argv[argc] = new_arg;
		argc++;
		ret = parse_redir(ret, ps, es);
	}

	_argv[argc] = 0;
	cmd->argv = _argv;
	cmd->argc = argc;

	return (ret);
}

// todo replace with generic function
// returns a allocated 2d_arr
char **create_argv(int nbr)
{
	return (ft_calloc((nbr + 1), sizeof(char *)));
}

// void create_arg( char **argv, char *str)
// {
// 	while (*argv)
// 		argv++;
// 	*argv = str;
// }
