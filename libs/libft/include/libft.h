/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:47:56 by pfelix-o          #+#    #+#             */
/*   Updated: 2024/05/09 16:46:48 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdbool.h>
# include <fcntl.h>
# include "libft_define.h"

// checker
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isspace(char c);
int		ft_issignal(char c);
bool	ft_ismax(int this, int that);

// converters
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_atoi(const char *str);
long	ft_atol(const char *str);
float	ft_atof(const char *str);
char	*ft_itoa(int n);
int		ft_abs(int n);

// memory
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t sz);
void	ft_bzero(void *s, size_t sz);
void	*ft_memmove(void *dst, const void *src, size_t sz);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t sz);
void	*ft_calloc(size_t nmemb, size_t sz);
char	*ft_strdup(const char *src);
void	ft_free_dptr(char **dptr);


//strings
size_t	ft_strlcpy(char *dst, const char *src, size_t sz);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t sz);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	**ft_split(char const *str, char c);
char	*get_next_line(int fd);
size_t	ft_strcount(const char *str, char c);

// output
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_printf(const char *format, ...);
int		ft_fprintf(int fd, const char *format, ...);
int		ft_dprintf(int fd, const char *format, ...);
char	*ft_sprintf(int fd, const char *format, ...);

// lists
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// dependencies for other functions
// ft_printf
int		pf_sw_printf(va_list args, char format, int *pf_len);
int		ft_printf_parser(const char *format, va_list args, int *pf_len);
void	vput_str(char *str, int *pf_len);
int		ft_define_fd(int out);
void	vput_char(char c, int *pf_len);
// void	vput_char(char c, int *pf_len, ...);
void	vput_base(int nbr, unsigned int base, char format, int *pf_len);
void	vput_pointer(void *ptr, int *pf_len);
// get_next_line
char	*ft_nl_strjoin(char *s1, char *s2);
void	*ft_move_buffer(char *dst, char *src);
char	*ft_has_nl(char *str);
void	ft_clear_buffer(char *str);
size_t	ft_nl_strlen(char *str);
int		ft_check_error(char *buffer, int fd);

#endif
