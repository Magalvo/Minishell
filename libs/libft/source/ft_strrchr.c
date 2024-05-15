/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 20:40:44 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/01/29 17:17:56 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
// #include <stdio.h>
// #include <string.h>

/* from man
The strrchr() function returns a pointer
to the last occurrence of the character c in the string s.
*/
char	*ft_strrchr(const char *s, int c)
{
	size_t		len;
	const char	*s_ptr;

	len = ft_strlen(s);
	s_ptr = s;
	s += len;
	if (*s == '\0' && (char)c == '\0')
		return ((char *)s);
	s--;
	while ((char)c != *s)
	{
		if (!*s || s < s_ptr)
			return (0);
		s--;
	}
	return ((char *)s);
}
/*
int	main()
{
	const char *str = "Hello, world!";
	char searchChar = 'd';
	char *result = ft_strrchr(str, searchChar);
	char *stdResult = strrchr(str, searchChar);

	if (result != NULL) {
		printf("Using ft_strrchr: Found character '%c' \
			at position %ld\n", searchChar, result - str);
	} else {
		printf("Using ft_strrchr: Character '%c' \
			not found\n", searchChar);
	}

	if (stdResult != NULL) {
		printf("Using strrchr:    Found character '%c' \
			at position %ld\n", searchChar, stdResult - str);
	} else {
		printf("Using strrchr:    Character '%c' \
			not found\n", searchChar);
	}
	return 0;
}
*/
