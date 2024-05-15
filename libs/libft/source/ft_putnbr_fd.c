/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 00:13:49 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/01/29 17:17:56 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
Convert int to char, and write to fd
*/
void	ft_putnbr_fd(int n, int fd)
{
	char	digit;
	long	divisor;
	long	lnb;

	lnb = (long)n;
	divisor = 1;
	if (n < INT_MIN || n > INT_MAX)
		divisor = 0;
	if (divisor)
	{
		if (lnb < 0 && write(fd, "-", 1))
			lnb = -lnb;
		while (divisor * 10 <= lnb)
			divisor = divisor * 10;
		while (divisor)
		{
			digit = lnb / divisor + '0';
			write(fd, &digit, 1);
			lnb = lnb % divisor;
			divisor = divisor / 10;
		}
	}
}
