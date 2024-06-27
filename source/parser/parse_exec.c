/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:28:53 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/06/27 18:29:31 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// checks input for tokens and calls appropiate function
t_cmd	*parse_exec(char **ps, char *es, t_ms *s)
{
	t_cmd	*cmd;
	t_d_cmd	cmds;
	t_cmd	*ret;

	ret = cmd_exec();
	cmd = ret;
	ret = parse_redir(ret, ps, es, s);
	cmd->argv = create_dptr(count_argc(ps, es, s));
	cmds.one = cmd;
	cmds.two = ret;
	parse_args(ps, es, &cmds, s);
	cmd->argv[cmd->argc] = 0;
	cmd = cmds.one;
	ret = cmds.two;
	return (ret);
}

void	parse_args(char **ps, char *es, t_d_cmd *cmds, t_ms *s)
{
	char	*q;
	char	*eq;
	char	*new_arg;
	int		tok;

	q = NULL;
	eq = NULL;
	//cmds->one->argc = 0;
	while(!peek(ps, es, "|)&;"))
	{
		tok = get_token(ps, es, &q, &eq);
		if (tok == 0)
			break;
		if(tok != 'a')
			reprompt(INVALID_TOKEN, 1, s);
		new_arg = ft_calloc((eq - q) + 1, sizeof(char));
		ft_memmove((void *)new_arg, (void *)q, (eq - q));
		unglue_str(new_arg, new_arg + ft_strlen(new_arg));
		cmds->one->argv[cmds->one->argc] = remove_quotes(new_arg);
		cmds->one->argc++;
		cmds->two = parse_redir(cmds->two, ps, es, s);
	}
	//cmds->one->argv[cmds->one->argc] = NULL;
}



int	count_argc(char **ps, char *es, t_ms *s)
{
	char	*ps_cpy;
	char	*es_cpy;
	int		argc;
	int		tok;

	argc = 0;
	ps_cpy = *ps;
	es_cpy = es;
	while(!peek(ps, es, "|)&<>"))
	{
		tok=get_token(ps, es, NULL, NULL);
		if (tok == 0)
			break;
		if (tok != 'a')
			reprompt("ARGC_COUNT", 1, s);
		argc++;
	}
	*ps = ps_cpy;
	es = es_cpy;
	return (argc);
}
