/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:25:55 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/22 16:35:42 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
s: The string from which to create the substring.
start: The start index of the substring in the string 's'.
len: The maximum length of the substring
Returns the substring, NULL if the allocation fails
Allocates with malloc() and returns a substring from the string 's'.
The substring begins at index 'start' and is of maximum size 'len' */
char	*ft_substr(char const *s, unsigned int start, size_t sz)
{
	char	*newstr;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start > s_len)
		sz = 0;
	else if (sz > (s_len - start))
		sz = s_len - start;
	newstr = (char *)malloc(sizeof(char) * (sz + 1));
	if (!newstr)
		return (NULL);
	s += start;
	*(newstr + sz) = '\0';
	ft_memcpy(newstr, s, sz);
	return (newstr);
}
