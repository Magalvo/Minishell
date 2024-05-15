/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_define.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:18:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/01/04 22:15:33 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_DEFINE_H
# define LIBFT_DEFINE_H

// STRUCTS
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// get_next_line
# ifndef FD_MAX
#  define FD_MAX 1024
# endif
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// ft_printf
# ifndef HEXNUMS_UPPER
#  define HEXNUMS_UPPER	"0123456789ABCDEF"
# endif
# ifndef HEXNUMS
#  define HEXNUMS	"0123456789abcdef"
# endif
# ifndef PRINTF_ARGS
#  define PRINTF_ARGS	"cspdiuxX%"
# endif

// MACROS
// none yet

#endif
