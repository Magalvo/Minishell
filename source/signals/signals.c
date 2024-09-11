/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:25:28 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/09/09 22:48:24 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// check siginfo_DontUse
void	handler(int signo, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_ignore(struct sigaction *sa, int signal)
{
	struct sigaction	sa_origin;
	int					sa_origin_flags;

	sa_origin_flags = sa->sa_flags;
	sa->sa_handler = SIG_IGN;
	sa->sa_flags |= SA_SIGINFO;
	if (sigemptyset(&sa->sa_mask) != 0)
		return ;
	sigaction(signal, sa, &sa_origin);
	sa->sa_flags = sa_origin_flags;
}

t_sinfo	exit_pack(t_ms *s, t_cmd *cmd)
{
	static t_sinfo	sinfo;

	if (s)
		sinfo.s = s;
	if (cmd)
		sinfo.cmd = cmd;
	return (sinfo);
}

void	ft_exitdoc(int status)
{
	t_sinfo	sinfo;

	sinfo = exit_pack(NULL, NULL);
	if (sinfo.cmd)
		free_ast(sinfo.cmd);
	if (sinfo.s->env)
		free_env_list(sinfo.s->env);
	if (sinfo.s->export)
		free_env_list(sinfo.s->export);
	if (sinfo.s != NULL)
	{
		free_ast(sinfo.s->ast);
		sinfo.s->ast = NULL;
	}
	exit(status);
}

void	here_handler(int signal, siginfo_t *info, void *context)
{
	t_sinfo	sinfo;
	//t_d_cmd	cinfo;

	(void)info;
	(void)context;
	//cinfo = cmd_info(NULL, NULL);
	sinfo = exit_pack(NULL, NULL);
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		close(sinfo.cmd->fd);
		free_ast2(&sinfo.s->cmd_temp2);
		sinfo.s->exit_stat = 130;
		sinfo.s->error = true;
		//exit_minishell(sinfo.s, NULL);
	}
}
