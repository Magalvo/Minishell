/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:27:18 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/04/01 19:55:39 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_sprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		pf_len;
	char	*pf_str;
	char	*temp;

	pf_len = 0;
	pf_str = NULL;
	ft_define_fd(fd);
	va_start(args, format);
	pf_len = ft_printf_parser(format, args, &pf_len);
	va_end(args);


	while ((temp = get_next_line(fd)) != NULL)
		pf_str = temp;
	close(fd);
	return (pf_str);
}
