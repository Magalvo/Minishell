/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 22:55:26 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/01/29 17:17:56 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
// #include <unistd.h>
// #include <limits.h>

/*
Allocates (with malloc(3)) and returns a string
representing the integer received as an argument.
Negative numbers must be handled.
Returns
The string representing the integer.
NULL if the allocation fails.
*/

static char	*itoa_loop(int len, long divisor, long lnb, int signal)
{
	char	*itoa_str;
	int		i;

	i = 0;
	itoa_str = (char *)malloc(sizeof(char) * len);
	if (!itoa_str)
		return (NULL);
	if (signal == 1)
	{
		itoa_str[0] = '-';
		i = 1;
	}
	while (divisor)
	{
		itoa_str[i] = lnb / divisor + '0';
		lnb = lnb % divisor;
		divisor = divisor / 10;
		i++;
	}
	itoa_str[i] = '\0';
	return (itoa_str);
}

char	*ft_itoa(int n)
{
	long	divisor;
	long	lnb;
	char	*itoa_str;
	int		itoa_len;
	int		i;

	itoa_len = 2;
	lnb = (long)n;
	divisor = 1;
	i = 0;
	if (n < INT_MIN || n > INT_MAX)
		return (NULL);
	if (lnb < 0 && itoa_len++)
	{
		i = 1;
		lnb = -lnb;
	}
	while (divisor * 10 <= lnb && itoa_len++)
		divisor = divisor * 10;
	itoa_str = itoa_loop(itoa_len, divisor, lnb, i);
	return (itoa_str);
}
/*
int	main(void)
{
	int		number;
	char	*result;

	number = INT_MIN;
	result = ft_itoa(number);
	printf("%s", result);
	free(result);
	return (0);
}
*/
