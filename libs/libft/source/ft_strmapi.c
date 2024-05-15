/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:09:22 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/01/29 17:17:56 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
//#include <stdlib.h>
//#include <string.h>

/*
char uppercase(unsigned int i, char c)
{
	if (c >= 'a' && c <= 'z' )
		c -= 32;
	return (c);
}
*/

/*
Applies the function 'f' to each character of the
string 's', and passing its index as first argument
to create a new string (with malloc(3)) resulting
from successive applications of 'f'.
*/

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*result;

	i = 0;
	result = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!result)
	{
		return (NULL);
	}
	while (s[i])
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}

/*
int main()
{
	char *test = "Hello from 42";
	char *result = ft_strmapi(test, uppercase);

	printf("Error: ft_strmapi returned \"%s\"\n", result);
	free(result);
	return (0);
}
*/
