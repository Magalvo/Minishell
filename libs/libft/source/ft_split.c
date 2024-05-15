/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:27:46 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/05/09 19:09:00 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

// replaced with ft_free_dptr;
// static void	ft_free_split(char **result)
// {
// 	int		i;

// 	i = 0;
// 	while (result[i])
// 	{
// 		free(result[i]);
// 		i++;
// 	}
// 	free(result);
// }

/*	Count words on a given array using char c as a delimeter
	used to determine malloc() size */
static int	ft_count_words(char const *str, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str == c)
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		str++;
	}
	return (count);
}

/* Extract words into a new string, using char c as a delimeter */
static char	*ft_word2str(const char *str, char c)
{
	size_t		len;
	const char	*start;

	len = 0;
	start = str;
	while (*str && *str != c)
	{
		len++;
		str++;
	}
	return (ft_substr(start, 0, len));
}

/* create a **array from words returned by ft_word2str */
static char	**ft_str2arr(char **result, const char *str, char c, size_t count)
{
	size_t		i;

	i = 0;
	while (*str && i <= count)
	{
		if (*str != c)
		{
			result[i] = ft_word2str(str, c);
			if (!result[i])
			{
				ft_free_dptr(result);
				return (NULL);
			}
			while (*str && *str != c)
				str++;
			i++;
		}
		else
			str++;
	}
	result[i] = NULL;
	return (result);
}
// ft_free_split(result); replaced with ft_free_dptr(result);

/*
Allocates with malloc() and returns an array of strings obtained
by splitting 's' using the character 'c' as a delimiter.
The array must end with a NULL pointer.
str: The string to be split.
c: The delimiter character.
Returns the array of new strings resulting from the split.
		NULL if the allocation fails. */
char	**ft_split(char const *str, char c)
{
	char	**result;
	size_t	word_count;

	if (!str)
		return (NULL);
	word_count = ft_count_words(str, c);
	result = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	result = (ft_str2arr(result, str, c, word_count));
	return (result);
}
