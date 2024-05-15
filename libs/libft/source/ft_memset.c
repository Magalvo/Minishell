/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:26:31 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/01/29 17:17:56 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
// #include <stdio.h>
// #include <string.h>

/*
The memset() function fills the first n bytes of the memory area
pointed to by s with the constant byte c.
The memset() function returns a pointer to the memory area s.
*/

void	*ft_memset(void *s, int c, size_t n)
{
	char	*mem;

	mem = s;
	while (n-- > 0)
		*mem++ = c;
	return (s);
}
/*
int main() {
	char buffer[20]; // Create a character array to store the test data
	size_t size = sizeof(buffer);

	// Test with your ft_memset function
	ft_memset(buffer, 'A', size);
	printf("Using ft_memset: %s\n", buffer);
	// Test with the standard memset function for comparison
	memset(buffer, 'B', size);
	// Print the contents of the buffer
	printf("Using memset:    %s\n", buffer);

	return 0;
}
*/
