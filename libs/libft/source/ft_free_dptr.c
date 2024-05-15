/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_dptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:27:46 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/05/11 18:20:33 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

// frees a 2d array (double pointer)
void	ft_free_dptr(char **dptr)
{
	int		i;

	i = 0;
	if (dptr == NULL)
		return ;
	while (dptr[i])
	{
		free(dptr[i]);
		i++;
	}
	free(dptr);
}

// frees a double pointer array, passed by reference and sets it to NULL
// void	ft_free_dptr_null(char ***dptr)
// {
// 	int		i;

// 	i = 0;
// 	if (*dptr == NULL)
// 		return ;
// 	while ((*dptr)[i])
// 	{
// 		free((*dptr)[i]);
// 		i++;
// 	}
// 	free(dptr);
// 	dptr = NULL;
// }
