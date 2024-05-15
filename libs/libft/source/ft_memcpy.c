/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:26:31 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/01/29 17:17:56 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
//#include <stdio.h>
// #include <string.h>

/* From man
The memcpy() function copies n bytes from memory area src to memory area dest.
The memory areas must not overlap. Use memmove if the memory areas do overlap.
The memcpy() function returns a pointer to dest.
*/

void	*ft_memcpy(void *dst, const void *src, size_t sz)
{
	unsigned char	*d;
	unsigned char	*s;

	if (sz == 0 || dst == src)
		return (dst);
	d = dst;
	s = (unsigned char *)src;
	while (sz > 0)
	{
		*d++ = *s++;
		sz--;
	}
	return (dst);
}
/*
int main() {
	char src[] = "Hello, World!";
    char dest1[20];
    char dest2[20];

    ft_memcpy(dest1, src, strlen(src) + 1); // +1 to include the null terminator
    memcpy(dest2, src, strlen(src) + 1);
    if (strcmp(dest1, dest2) == 0) {
        printf("Using ft_memcpy: Copied string is \"%s\"\n", dest1);
		printf("Using ft_memcpy: Copied string is \"%s\"\n", dest2);
    } else {
        printf("Using ft_memcpy: Copying failed\n");
    }
    return 0;
}
*/
