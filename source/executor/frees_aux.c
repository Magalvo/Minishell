/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:15:46 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/08/16 18:21:28 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free2(char *one, char *two)
{
	if (one)
	{
		free(one);
		one = NULL;
	}
	if (two)
	{
		free(two);
		two = NULL;
	}
}

void	exit_doc(t_ms *s, int heredoc, t_cmd *cmd)
{
	del_eof(heredoc);
	free_herechild(&cmd);
	exit_minishell(s, NULL);
}

void	close_fd_child(t_cmd *cmd, int fd_in, int fd_out)
{
	(void)cmd;
	close_fd(&fd_in);
	close_fd(&fd_out);
}
