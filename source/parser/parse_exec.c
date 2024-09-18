/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:28:53 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/09/18 14:17:37 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cinfo	cmd_info(t_cmd *cmd, int clear)
{
	static t_cinfo	cinfo;
	int				i;

	i = 0;
	if (clear == 1)
	{
		while (cinfo.cmd[i] != NULL)
		{
			cinfo.cmd[i] = NULL;
			i++;
		}
		return (cinfo);
	}
	if (cmd)
	{
		while (cinfo.cmd[i] != NULL)
			i++;
		cinfo.cmd[i] = cmd;
	}
	return (cinfo);
}

// checks input for tokens and calls appropiate function
t_cmd	*parse_exec(char **ps, char *es, t_ms *s)
{
	t_cmd	*cmd;
	t_d_cmd	cmds;
	t_cmd	*ret;
	int		argc;

	cmd = NULL;
	ret = cmd_exec(s);
	cmd = ret;
	ret = parse_redir(ret, ps, es, s);
	if (ret == NULL)
		return (NULL);
	argc = count_argc(ps, es, s);
	cmd->argv = create_dptr(argc);
	cmds.one = cmd;
	cmds.two = ret;
	parse_args(ps, es, &cmds, s);
	if (cmds.two == NULL)
		return (NULL);
	cmd->argv[cmd->argc] = NULL;
	cmd = cmds.one;
	ret = cmds.two;
	if (s->error == true)
		return (NULL);
	return (ret);
}

void	parse_args_exec(t_d_cmd *cmds, t_ms *s)
{
	(void)s;
	if (cmds && !cmds->two)
	{
		if (cmds->one)
		{	
			free_ast(cmds->one);
		}
		ft_dprintf(2, "ESTRELA GUIATE \n");
	}
}

void	parse_args(char **ps, char *es, t_d_cmd *cmds, t_ms *s)
{
	char	*q;
	char	*eq;
	char	*new_arg;
	int		tok;

	q = NULL;
	eq = NULL;
	while (!peek(ps, es, "|"))
	{
		tok = get_token(ps, es, &q, &eq);
		if (tok == 0 || (tok != 'a' && s->error == true))
		{
			if (s->error == true && s->exit_stat == 130)
				free_ast(cmds->one);
			break ;
		}
		else if (tok != 'a')
			reprompt(NOT_A_VALID_TOKEN, 1, s);
		new_arg = ft_calloc((eq - q) + 1, sizeof(char));
		ft_memmove((void *)new_arg, (void *)q, (eq - q));
		unglue_str(new_arg, new_arg + ft_strlen(new_arg));
		new_arg = expand_sw_vars(new_arg, s);
		if (s->error == true)
		{
			if (new_arg != NULL)
				free(new_arg);
			new_arg = NULL;
			break; 
		}
		cmds->one->argv[cmds->one->argc] = reassemble_input(new_arg);
		cmds->one->argc++;
		cmds->two = parse_redir(cmds->two, ps, es, s);
	}
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
	while (!peek(ps, es, TOKENS))
	{
		tok = get_token(ps, es, NULL, NULL);
		if (tok == 0)
			break ;
		if (tok != 'a')
			reprompt("ARGC_COUNT", 1, s);
		argc++;
		parse_fake_redir(ps, es, s);
	}
	*ps = ps_cpy;
	es = es_cpy;
	return (argc);
}
