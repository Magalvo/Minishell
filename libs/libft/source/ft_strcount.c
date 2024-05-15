/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:27:46 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/05/09 16:48:24 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

// counts the number of times 'c' occurs on *str
size_t	ft_strcount(const char *str, char c)
{
	size_t count = 0;

	while (*str) {
		if (*str == c)
			count++;
		str++;
	}
	return count;
}
