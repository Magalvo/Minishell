/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:42:24 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/01/29 17:17:56 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
// #include <stdlib.h>
// #include <stdint.h>

/*
void	*ft_memset(void *s, int c, size_t n)
{
	char	*mem;

	mem = s;
	while (n-- > 0)
		*mem++ = c;
	return (s);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}
*/

/*
The calloc() function allocates memory for an array of nmemb elements
of size bytes each and returns a pointer to the allocated memory. The
memory is set to zero. If nmemb or size is 0, then calloc() returns
either NULL, or a unique pointer value that can later be successfully
passed to free(). If the multiplication of nmemb and size would result
in integer overflow, then calloc() returns an error. By contrast, an
integer overflow would not be detected in the following call to malloc(),
with the result that an incorrectly sized block of memory would
be allocated:	malloc(nmemb * size);
If error returns empty void to be free() // <- read with salt
*/

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*newmem;

	if (nmemb && size && (SIZE_MAX / size < nmemb))
	{
		return (NULL);
	}
	newmem = malloc(size * nmemb);
	if (!newmem)
	{
		return (NULL);
	}
	ft_bzero(newmem, size * nmemb);
	return (newmem);
}

/*
void test_ft_calloc(size_t nmemb, size_t size)
{
	void *ptr = ft_calloc(nmemb, size);
	if (ptr == NULL)
	{
		printf("ft_calloc returned NULL\n");
		return;
	}

	size_t total_size = nmemb * size;
	char *char_ptr = (char *)ptr;
	for (size_t i = 0; i < total_size; i++)
	{
		if (char_ptr[i] != 0)
		{
			printf("ft_calloc did not set memory to 0\n");
			free(ptr);
			return;
		}
	}

	printf("ft_calloc test passed\n");
	free(ptr);
}

int main()
{
	test_ft_calloc(0, 10);
	test_ft_calloc(10, 0);
	test_ft_calloc(10, 1);
	test_ft_calloc(1, 10);
	test_ft_calloc(100, 100);
	test_ft_calloc(SIZE_MAX, 1);
	test_ft_calloc(1, SIZE_MAX);
	test_ft_calloc(SIZE_MAX, SIZE_MAX);
	return 0;
}
*/
