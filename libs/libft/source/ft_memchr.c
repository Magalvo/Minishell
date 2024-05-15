/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:26:31 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/01/29 17:17:56 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
The memchr() function scans the initial n bytes of the memory area
pointed to by s for the first instance of c.
Both c and the bytes of the memory area pointed to by s
are interpreted as unsigned char.
The memchr() and memrchr() functions return a pointer to the matching byte
or NULL if the character does not occur in the given memory area.
*/

void	*ft_memchr(const void *s, int c, size_t sz)
{
	const unsigned char	*s_cp;

	s_cp = (const unsigned char *) s;
	while (sz-- > 0)
	{
		if (*s_cp == (unsigned char)c)
			return ((char *)s_cp);
		s_cp++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

void	test_ft_memchr(void)
{
    const char *str = "Hello, world!";
    char *result;

    // Test case 1: character is found in string
    result = ft_memchr(str, 'o', strlen(str));
    if (result == strchr(str, 'o'))
        printf("Test case 1 passed\n");
    else
        printf("Test case 1 failed\n");

    // Test case 2: character is not found in string
    result = ft_memchr(str, 'z', strlen(str));
    if (result == NULL)
        printf("Test case 2 passed\n");
    else
        printf("Test case 2 failed\n");

    // Test case 3: character is at the beginning of the string
    result = ft_memchr(str, 'H', strlen(str));
    if (result == str)
        printf("Test case 3 passed\n");
    else
        printf("Test case 3 failed\n");

    // Test case 4: character is at the end of the string
    result = ft_memchr(str, '!', strlen(str));
    if (result == strchr(str, '!'))
        printf("Test case 4 passed\n");
    else
        printf("Test case 4 failed\n");
}

int	main(void)
{
    test_ft_memchr();
    return (0);
}
*/
