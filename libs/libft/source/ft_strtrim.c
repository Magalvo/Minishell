/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:27:33 by davidro2          #+#    #+#             */
/*   Updated: 2024/01/29 17:17:56 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

/*
from project PDF
s1: The string to be trimmed.
set: The reference set of characters to trim.
Allocates (with malloc(3)) and returns a copy of 's1' with the characters
specified in 'set' removed from the beginning and the end of the string.
Returns the trimmed string. NULL if the allocation fails.
*/
char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*trim;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	str = (char *)s1;
	while (ft_strchr(set, *(str)))
	{
		str++;
		start++;
	}
	while (ft_strchr(set, *(s1 + end - 1)))
		end--;
	trim = ft_substr(s1, start, end - start);
	if (!trim)
	{
		return (NULL);
	}
	return (trim);
}

/*
int main()
{
	char *s1 = "   Hello from 42!   ";
	char *set = " ";
	char *expected_result = "Hello from 42!";
	char *result = ft_strtrim(s1, set);

	if (result == NULL)
	{
		printf("Error: ft_strtrim returned NULL\n");
		return 1;
	}
	{
	printf("ft_strtrim returned \"%s\", expected \"%s\"\n", \
		result, expected_result);
	if (ft_strcmp(result, expected_result) != 0)
		printf("Test failed\n");
	else if (ft_strcmp(result, expected_result) == 0))
		printf("Test passed\n");
	free(result);
	return 0;
}
*/
