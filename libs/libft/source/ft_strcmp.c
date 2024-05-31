/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:45:38 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/27 14:28:00 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int ft_strcmp(const char *s1, const char *s2) {
    size_t s1_len = ft_strlen(s1);
    size_t s2_len = ft_strlen(s2);

    if (s1_len != s2_len) {
        return (s1_len - s2_len);
    }
    return ft_strncmp(s1, s2, s1_len);
}

//int big_asci(const char *s1, const char *s2)
