/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 20:40:44 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/01/29 17:17:56 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
//#include <stdio.h>

/*
size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len++] != '\0')
		;
	return (len - 1);
}

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
		return(0);
	return ((uint8_t)*s1 - (uint8_t)*s2);
}
*/

/*
Further references:
https://opensource.apple.com/source/Libc/Libc-391.2.3/string/
		FreeBSD/strnstr.c.auto.html
Find the first occurrence of needle in haystack,
where the search is limited to the first n characters of haystack */
char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	if (!n && !haystack)
		return (NULL);
	if (!*needle)
		return ((char *)haystack);
	while (*haystack && needle_len <= n)
	{
		if (*haystack == *needle)
		{
			if (ft_strncmp((char *)haystack, (char *)needle, needle_len) == 0)
				return ((char *)haystack);
		}
		haystack++;
		n--;
	}
	return (NULL);
}

/*
int	main(void)
{
	char	*agulha;
	char	*palheiro;
	char	*lstrstr;

	agulha = "from";
	palheiro = "hello from 42";
	lstrstr = ft_strnstr("lorem ipsum dolor sit amet", "dolor", 0)))
	//lstrstr = ft_strnstr(palheiro, agulha, 10);
	if (lstrstr == NULL)
		printf("no substring found\n");
	else
		printf("substring found at '%s'\n", lstrstr);
	return (0);
}
*/
