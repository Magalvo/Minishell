/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:26:31 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/01/29 17:17:56 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
// #include <stdio.h>
// #include <string.h>

/* DESCRIPTION
	The  memcmp()  function compares the first n bytes (each interpreted as un‐
	signed char) of the memory areas s1 and s2.

RETURN VALUE
	The memcmp() function returns an integer less than, equal  to,  or  greater
	than  zero  if  the  first n bytes of s1 is found, respectively, to be less
	than, to match, or be greater than the first n bytes of s2.

	For a nonzero return value, the sign is determined by the sign of the dif‐
	ference between the first pair of bytes (interpreted as unsigned char) that
	differ in s1 and s2.

	If n is zero, the return value is zero. */

int	ft_memcmp(const void *s1, const void *s2, size_t sz)
{
	const unsigned char	*s1_cp;
	const unsigned char	*s2_cp;

	if (sz > 0)
	{
		s1_cp = (const unsigned char *) s1;
		s2_cp = (const unsigned char *) s2;
		while (sz-- > 0)
		{
			if (*s1_cp++ != *s2_cp++)
				return (*--s1_cp - *--s2_cp);
		}
	}
	return (0);
}
/*
int main()
{
	// Test case 1: Compare two identical strings
	char str1[] = "Hello, world!";
	char str2[] = "Hello, world!";
	int res1 = ft_memcmp(str1, str2, strlen(str1));
	int res2 = memcmp(str1, str2, strlen(str1));
	printf("Test case 1: %s\n", (res1 == res2) ? "Passed" : "Failed");

	// Test case 2: Compare two different strings
	char str3[] = "Hello, world!";
	char str4[] = "Goodbye, world!";
	int res3 = ft_memcmp(str3, str4, strlen(str3));
	int res4 = memcmp(str3, str4, strlen(str3));
	printf("Test case 2: %s\n", (res3 == res4) ? "Passed" : "Failed");

	// Test case 3: Compare two strings with different lengths
	char str5[] = "Hello, world!";
	char str6[] = "Hello, world";
	int res5 = ft_memcmp(str5, str6, strlen(str5));
	int res6 = memcmp(str5, str6, strlen(str5));
	printf("Test case 3: %s\n", (res5 == res6) ? "Passed" : "Failed");

	// Test case 4: Compare two empty strings
	char str7[] = "";
	char str8[] = "";
	int res7 = ft_memcmp(str7, str8, strlen(str7));
	int res8 = memcmp(str7, str8, strlen(str7));
	printf("Test case 4: %s\n", (res7 == res8) ? "Passed" : "Failed");

	// Test case 5: Compare two strings with different lengths
	char str9[] = "Hello, world!";
	char str10[] = "Hello, world!!";
	int res9 = ft_memcmp(str9, str10, strlen(str9));
	int res10 = memcmp(str9, str10, strlen(str9));
	printf("Test case 5: %s\n", (res9 == res10) ? "Passed" : "Failed");

	// Test case 6: Compare two strings with different lengths
	char str11[] = "Hello, world!!";
	char str12[] = "Hello, world!";
	int res11 = ft_memcmp(str11, str12, strlen(str11));
	int res12 = memcmp(str11, str12, strlen(str11));
	printf("Test case 6: %s\n", (res11 == res12) ? "Passed" : "Failed");

	// Test case 7: Compare two strings with different lengths
	char str13[] = "Hello, world!";
	char str14[] = "Hello, world!!";
	int res13 = ft_memcmp(str13, str14, strlen(str14));
	int res14 = memcmp(str13, str14, strlen(str14));
	printf("Test case 7: %s\n", (res13 == res14) ? "Passed" : "Failed");

	// Test case 8: Compare two strings with different lengths
	char str15[] = "Hello, world!!";
	char str16[] = "Hello, world!";
	int res15 = ft_memcmp(str15, str16, strlen(str15));
	int res16 = memcmp(str15, str16, strlen(str15));
	printf("Test case 8: %s\n", (res15 == res16) ? "Passed" : "Failed");

	// Test case 9: Compare two identical strings with size 0
	char str17[] = "Hello, world!";
	char str18[] = "Hello, world!";
	int res17 = ft_memcmp(str17, str18, 0);
	int res18 = memcmp(str17, str18, 0);
	printf("Test case 9: %s\n", (res17 == res18) ? "Passed" : "Failed");

	// Test case 10: Compare two different strings with size 0
	char str19[] = "Hello, world!";
	char str20[] = "Goodbye, world!";
	int res19 = ft_memcmp(str19, str20, 0);
	int res20 = memcmp(str19, str20, 0);
	printf("Test case 10: %s\n", (res19 == res20) ? "Passed" : "Failed");

	return 0;
}
*/
