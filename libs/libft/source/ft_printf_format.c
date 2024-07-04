/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:27:18 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/01/29 17:17:56 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_define_fd(int out)
{
	static int	fd;

	if (out != -1)
		fd = out;
	return (fd);
}

void	vput_char(char c, int *pf_len)
{
	static int	fd;

	fd = ft_define_fd(-1);
	write(fd, &c, 1);
	(*pf_len)++;
}

void	vput_str(char *str, int *pf_len)
{
	size_t	str_len;

	str_len = 0;
	if (!str)
		str = "(null)";
	while (str[str_len] != '\0')
	{
		vput_char(str[str_len], pf_len);
		str_len++;
	}
}

// Handles all INT except pointer address
void	vput_base(int nbr, unsigned int base, char format, int *pf_len)
{
	char			digit;
	unsigned int	lnbr;

	lnbr = nbr;
	if (nbr < 0 && base != 16 && format != 'u' && format != 'p')
	{
		lnbr = (unsigned int)-nbr;
		vput_char('-', pf_len);
	}
	else if (format == 'p')
		lnbr = (unsigned long long)nbr;
	if (lnbr >= base)
		vput_base(lnbr / base, base, format, pf_len);
	if (format == 'X')
		digit = HEXNUMS_UPPER[lnbr % base];
	else
		digit = HEXNUMS[lnbr % base];
	vput_char(digit, pf_len);
}

// bitwise algorithm. 1 byte = 2 nibbles (4 bits)
// iterations calculates how many hex digits (nibbles).
// Extract the first nibble of address and checks if == 0,
// until digit != 0 (leading zeros are done) keep looping.
// On each loop shifts 1 nibble to the left.
// set bool found_non_zero == true and print every digit.

// Pointer address are "special" and so am I, so function just for it
void	vput_pointer(void *ptr, int *pf_len)
{
	uintptr_t	address;
	int			iterations;
	int			found_non_zero;
	char		digit;

	address = (uintptr_t)ptr;
	if (address == 0)
	{
		vput_str("(nil)", pf_len);
		return ;
	}
	iterations = sizeof(uintptr_t) * 2;
	found_non_zero = 0;
	vput_str("0x", pf_len);
	while (iterations--)
	{
		digit = HEXNUMS[address >> (sizeof(uintptr_t) * 8 - 4)];
		if (digit != '0' || found_non_zero)
		{
			vput_char(digit, pf_len);
			found_non_zero = 1;
		}
		address <<= 4;
	}
}
