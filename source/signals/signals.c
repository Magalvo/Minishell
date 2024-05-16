/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:16:49 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/16 14:50:13 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

//use write() and not printf() for handling SIGNALS // MIGHT CRASH

int	handle_signal(int num)
{
	write (1, "\n", 1);
	write (1, "Exit", 4);
	exit(1);	
}