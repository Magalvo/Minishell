/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:25:28 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/09/03 18:29:13 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_signal(t_signal sig)
{
	static struct sigaction	sa;

	if (sig == MAIN)
		signal_main(sa);
	else if (sig == CHILD)
		signal_child(sa);
	else if (sig == HERE_DOC)
		signal_heredoc(sa);
	else if (sig == IGNORE)
	{
		sig_ignore(&sa, SIGINT);
		sig_ignore(&sa, SIGQUIT);
	}
}

void	signal_main(struct sigaction sa)
{
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigemptyset(&sa.sa_mask) != 0)
		return ;
	sigaction (SIGINT, &sa, NULL);
	sig_ignore(&sa, SIGQUIT);
}

void	signal_child(struct sigaction sa)
{
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	if (sigemptyset(&sa.sa_mask) != 0)
		return ;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	signal_heredoc(struct sigaction sa)
{
	sa.sa_sigaction = here_handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigemptyset(&sa.sa_mask) != 0)
		return ;
	sigaction(SIGINT, &sa, NULL);
	sig_ignore(&sa, SIGQUIT);
}
