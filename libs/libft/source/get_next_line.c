/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:17:44 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/04/03 15:45:41 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_nl_strjoin(char *s1, char *s2)
{
	char	*join;
	size_t	s1_len;
	size_t	s2_len;
	size_t	join_len;
	size_t	i;

	s1_len = ft_nl_strlen(s1);
	s2_len = ft_nl_strlen(s2);
	join_len = s1_len + s2_len;
	join = (char *)malloc(sizeof(char) * (join_len) + 1);
	if (join == NULL)
		return (NULL);
	i = 0;
	if (s1)
		while (*s1 && s1_len--)
			join[i++] = *s1++;
	while (*s2 && s2_len-- && *s2)
		join[i++] = *s2++;
	join[i] = '\0';
	return (join);
}

void	*ft_move_buffer(char *dst, char *src)
{
	size_t	sz;
	size_t	i;

	if (!*++src || !src)
	{
		ft_clear_buffer(dst);
		return (0);
	}
	sz = 0;
	while (*src++ != '\0')
		sz++;
	src = src - sz - 1;
	i = sz;
	while (i)
	{
		*dst++ = *src++;
		i--;
	}
	if (sz <= BUFFER_SIZE)
		ft_clear_buffer(dst);
	return (0);
}

int	ft_check_error(char *buffer, int fd)
{
	if (BUFFER_SIZE < 0 || fd < 0 || fd >= FD_MAX)
		return (1);
	else if (read(fd, 0, 0) < 0)
	{
		ft_clear_buffer(buffer);
		return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buffer[FD_MAX][BUFFER_SIZE + 1];
	char		*stuff;
	char		*line;

	if (ft_check_error(buffer[fd], fd))
		return (NULL);
	line = NULL;
	while (*buffer[fd] != 0 || read(fd, buffer[fd], BUFFER_SIZE))
	{
		stuff = line;
		line = ft_nl_strjoin(stuff, buffer[fd]);
		free(stuff);
		stuff = ft_has_nl(buffer[fd]);
		if (stuff)
		{
			ft_move_buffer(buffer[fd], stuff);
			break ;
		}
		else
			ft_clear_buffer(buffer[fd]);
	}
	return (line);
}
