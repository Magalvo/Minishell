/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 22:08:50 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/01/29 17:17:56 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
// #include <stdio.h>

/*
from man
The strcmp() function compares the two strings s1 and s2. It returns an integer
less than, equal to, or greater than zero if s1 is found, respectively,
to be less than, to match, or be greater than s2.
The strncmp() function is similar, except it compares only the first (at most) n
bytes of s1 and s2.
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0 && *s1 && *s2)
	{
		if (*s1 != *s2)
			break ;
		n--;
		s1++;
		s2++;
	}
	if (n == 0)
		return (0);
	return ((uint8_t) * s1 - (uint8_t) * s2);
}
/*
int main() {
	char str1[] = "Hello";
	char str2[] = "Hello";

	int result = ft_strncmp(str1, str2, 4);

	if (result == 0) {
		printf("Strings are equal.\n");
	} else if (result < 0) {
		printf("String 1 is less than String 2.\n");
	} else {
		printf("String 1 is greater than String 2.\n");
	}

	return 0;
}
*/
