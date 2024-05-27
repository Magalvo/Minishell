/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:40:06 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/27 12:48:31 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	error_msg(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}
int	free_export(char *key, char *value)
{
		free(key);
		free(value);
		return (error_msg("failed to create new node"), 0);
}