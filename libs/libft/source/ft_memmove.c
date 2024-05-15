/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:26:31 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/01/29 17:17:56 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
// #include <stdint.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

/*
The	memmove(void) function copies n bytes from memory area src
to memory area dest.
The memory areas may overlap: copying takes place as though
the bytes in src are first copied into a temporary array
that does not overlap src or dest, and the bytes are then copied
from the temporary array to dest.
	The memmove() function returns a pointer to dest.
*/

void	*ft_memmove(void *dst, const void *src, size_t sz)
{
	size_t	i;

	i = 0;
	if (src == dst || sz == 0)
		return (dst);
	if (dst > src)
	{
		i = sz;
		while (i-- > 0)
		{
			((uint8_t *)dst)[i] = ((uint8_t *)src)[i];
		}
	}
	else if (dst < src)
	{
		while (i < sz)
		{
			((uint8_t *)dst)[i] = ((uint8_t *)src)[i];
			i++;
		}
	}
	return (dst);
}

/*
int	main(void)
{
	char	dst[12];
	char	*result;

	char src[] = "hello world";
	// Test case 1: Copying from src to dst without overlap
	result = ft_memmove(dst, src, 12);
	if (result == dst && strcmp(dst, "hello world") == 0)
	{
		printf("Test case 1 passed!\n");
	}
	else
	{
		printf("Test case 1 failed!\n");
	}
	// Test case 2: Copying from src to dst with overlap (forward copy)
	result = ft_memmove(dst + 6, dst, 5);
	if (result == dst + 6 && strcmp(dst, "hello hello") == 0)
	{
		printf("Test case 2 passed!\n");
	}
	else
	{
		printf("Test case 2 failed!\n");
	}
	// Test case 3: Copying from src to dst with overlap (reverse copy)
	result = ft_memmove(dst, dst + 6, 5);
	if (result == dst && strcmp(dst, "hello hello") == 0)
	{
		printf("Test case 3 passed!\n");
	}
	else
	{
		printf("Test case 3 failed!\n");
	}
	return (0);
}
*/
