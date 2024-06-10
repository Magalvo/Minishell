
#include "../include/minishell.h"

void	ft_strreplace(char *start, char *end, char search, char replace)
{
	char *ptr;

	if (start == NULL)
		return ;
	ptr = start;
	while (ptr != end && *ptr != '\0')
	{
		if (*ptr == search)
			*ptr = replace;
		ptr++;

	}
}


void	glue(char *start, char *end, char search, char replace)
{


}
