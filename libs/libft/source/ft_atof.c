/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 21:18:01 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/03/30 13:43:14 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

// see ft_atoi and ft_atol for further info. Added for Fractol project
float	ft_atof(const char *str)
{
	float	signal;
	float	result;

	signal = 1.0;
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
		result = result * 10 + *str++ - '0';
	if (*str++ == '.')
	{
		while (ft_isdigit(*str) && *str)
		{
			result = result * 10 + *str++ - '0';
			signal *= 0.1;
		}
	}
	return (result * signal);
}
