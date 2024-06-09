
#include "../include/minishell.h"

// checks input for tokens and calls appropiate function
// returns a 2d_arr with the found symbols
// TODO break in 2 or 3 - so many lines ;(
t_cmd *parse_exec(char **ps, char *es)
{
	char	*q;
	char	*eq;
	int		tok;
	int		_argc;
	t_cmd	*cmd;
	t_cmd	*ret;
	char	*new_arg;
	char	**_argv;

	if(peek(ps, es, "("))
		return (parse_block(ps, es));
	ret = cmd_exec();
	cmd = ret;
	// argc = 0;

	ret = parse_redir(ret, ps, es);
	// argc = count_argc(ps, es, );
	// char *ps_cpy = *ps;
	// char *es_cpy = es;
	// while(!peek(ps, es, "|)&;"))
	// {
	// 	if((tok=get_token(ps, es, &q, &eq)) == 0)
	// 		break;
	// 	if(tok != 'a')
	// 		reprompt(INVALID_TOKEN);
	// 	argc++;
	// }

	// _argv = create_argv(argc);
	_argv = create_argv(count_argc(ps, es));
	// (void)_argv;

	// *ps = ps_cpy;
	// es = es_cpy;
	_argc = 0;
	while(!peek(ps, es, "|)&;"))
	{
		if((tok=get_token(ps, es, &q, &eq)) == 0)
			break;
		if(tok != 'a')
			reprompt(INVALID_TOKEN);
		new_arg = ft_calloc((eq - q) + 1, sizeof(char));
		ft_memmove((void *)new_arg, (void *)q, (eq - q));
		_argv[_argc] = new_arg;
		_argc++;
		ret = parse_redir(ret, ps, es);
	}
	_argv[_argc] = 0;
	cmd->argv = _argv;
	cmd->argc = _argc;

	return (ret);
}

// todo replace with generic function
// returns a allocated 2d_arr
char **create_argv(int nbr)
{
	return (ft_calloc((nbr + 1), sizeof(char *)));
}

int	count_argc(char **ps, char *es)
{
	char	*ps_cpy;
	char	*es_cpy;
	int		argc;
	// t_cmd	*ret;
	int		tok;

	// char	*q;
	// char	*eq;
	argc = 0;
	ps_cpy = *ps;
	es_cpy = es;
	// ret = cmd_exec();
	while(!peek(ps, es, "|)&<>")){
		// tok=get_token(ps, es, &q, &eq);
		tok=get_token(ps, es, NULL, NULL);
		if (tok == 0)
			break;
		if (tok != 'a')
			reprompt("ARGC_COUNT");
		argc++;
		// ret = parse_redir(ret, ps, es);
	}
	// free(ret);
	*ps = ps_cpy;
	es = es_cpy;
	return (argc);
}
