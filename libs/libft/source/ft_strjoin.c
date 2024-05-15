/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 21:20:48 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/01/29 17:17:56 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
// #include <stdlib.h>

/*
size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len++] != '\0')
		;
	return (len - 1);
}
*/

/* Parameters
	s1: The prefix string.
	s2: The suffix string.
Returns new string, NULL if the allocation fails.
Allocates (with malloc(3)) and returns a new
string, which is the result of the concatenation
of 's1' and 's2'. */

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	s1_len;
	size_t	s2_len;
	size_t	join_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join_len = s1_len + s2_len;
	join = (char *)malloc(sizeof(char) * (join_len + 1));
	if (join == NULL)
		return (NULL);
	if (s1)
	{
		while (*s1 && s1_len--)
			*join++ = *s1++;
	}
	while (*s2 && s2_len--)
		*join++ = *s2++;
	*join = '\0';
	return (join - join_len);
}

/*
int	main(void)
{
	char	*result;

	result = ft_strjoin("aa", "bb");
	printf("%s\n", result);
	return (0);
}
*/
