/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:15:41 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/01/29 17:17:56 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
// #include <stdio.h>

/*
size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}
*/
/*
// from man:	TIP: check man strlcpy
This function copy and catenate the input string into a destination string.
If the destination buffer, limited by its size, isn't large enough to hold the
copy, the resulting string is truncated (but it is guaranteed to be
null‐terminated).
They return the length of the total string they tried to create. This function
force a SIGSEGV if the src pointer is not a string.
// Personal Note
This implementation DOES NOT garantee for null terminated string when truncated.
Won't pass some tests is null-terminated is enforced.
To fix: *** dst[dst_len + i] = '\0'; *** must change to i -1
TIP: check man strlcpy
*/

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if (size < dst_len)
		return (src_len + size);
	while (src[i] && dst_len + i + 1 < size)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (src_len + dst_len);
}

/*
int	main(void)
{
	char			dest[20] = "he1lo ";
	char			src[] = "world!";
	unsigned int 	result;
	unsigned int	n;

	n = 10;
	printf("%s\n", dest);
	printf("%s\n", src);
	printf("%d\n", ft_strlen(dest));
	printf("%d\n", ft_strlen(src));
	result = ft_strlcat(dest, src, n);
	printf("%s\n", dest);
	printf("%d\n", result);
	return (0);
}
*/
