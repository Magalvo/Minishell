/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 21:18:01 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/01/29 17:17:56 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
// #include <stdio.h>

// static int	ft_isspace(char c)
// {
// 	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
// 		|| c == ' ');
// }
/*
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
*/
/*
alphanumeric to int
*/

int	ft_atoi(const char *str)
{
	int		signal;
	long	result;

	signal = 1;
	result = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signal = -1;
		str++;
	}
	while (ft_isdigit(*str) && *str)
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * signal);
}
/*
int	main(int argc, char *argv[])
{
	if (argc == 1)
		printf("No command-line arguments provided.\n");
	else
	{
		printf("%i\n", ft_atoi(argv[1]));
		printf("Number of command-line arguments: %d\n", argc - 1);
		for (int i = 1; i < argc; i++)
		{
			printf("Argument %d: %s\n", i, argv[i]);
		}
		// printf("%d\n", ft_atoi(argv[1]));
	}
	//printf("%d\n", ft_atoi("   -1234ab567"));
	// ft_atoi(argv[1]);

	return (0);
}
*/
