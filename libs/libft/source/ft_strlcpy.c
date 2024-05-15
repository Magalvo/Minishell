/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:26:31 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/01/29 17:17:56 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
// #include <stddef.h>
// #include <stdio.h>
// #include <string.h>

/*
excert from man:  TIP: check man strlcpy
The strlcpy() function copies up to size - 1 characters from
the NUL-terminated string src to dst, NUL-terminating the result.
Return the total length of the string they tried to create.
For strlcpy() that means the length of src.
TIP: check man strlcpy
*/

size_t	ft_strlcpy(char *dst, const char *src, size_t sz)
{
	size_t	srclen;

	srclen = ft_strlen(src);
	if (srclen + 1 < sz)
	{
		ft_memcpy(dst, src, srclen + 1);
	}
	else if (sz != 0)
	{
		ft_memcpy(dst, src, sz - 1);
		dst[sz - 1] = '\0';
	}
	return (srclen);
}

/*
int	main(void)
{
	size_t	n;
	unsigned int	copied;
	char			dest[20];
	char			src[] = {"hello from 42"};

	n = 2;
	copied = 0;
	printf("\nBefore strcpy\n");
	printf("copied: %d\n", copied);
	copied = ft_strlcpy(dest, src, n);
	printf("\nAfter ft_strlcpy\n");
	printf("src: %s\n", src);
	printf("dest: %s\n", dest);
	printf("copied: %d\n", copied);
	copied =strlcpy(dest, src, n);
	printf("\nAfter strlcpy\n");
	printf("src: %s\n", src);
	printf("dest: %s\n", dest);
	printf("copied: %d\n", copied);
	return (0);
}
*/
