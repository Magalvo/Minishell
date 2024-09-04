/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:25:28 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/06/27 18:04:11 by cjoao-de         ###   ########.fr       */
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

	(void)sinfo;
	(void)status;
	sinfo = exit_pack(NULL, NULL);


}

void	here_handler(int signal, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	t_sinfo	sinfo;

	sinfo = exit_pack(NULL, NULL);
	if (signal == SIGINT)
	{
		printf("\n");
		sinfo.s->exit_stat = 130;
		close(sinfo.cmd->fd);
		/* if (sinfo.cmd->delim != NULL)
			free(sinfo.cmd->delim);
		if (sinfo.s->cmd_temp != NULL)
			free(sinfo.s->cmd_temp); */
	}
}
