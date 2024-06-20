/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:59:04 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/21 16:59:27 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_cmd(t_ms *s, int status)
{
	if (!status)
		status = s->exit_stat;
	if (s->ast)
		free_ast(s->ast);
	exit(status);
}
