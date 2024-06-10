
#include "../include/minishell.h"

// replaces -search- with -replace- on the range between *start and *end
// if end is NULL, searches until end of string.
void	ft_strrep_range(char *start, char *end, char search, char replace)
{
	char *ptr;

	if (start == NULL)
		return ;
	ptr = start;
	if (end == NULL)
	{
		while (*ptr != '\0')
		{
			if (*ptr == search)
				*ptr = replace;
			ptr++;

		}
	}
	else
	{
		while (ptr != end)
		{
			if (*ptr == search)
				*ptr = replace;
			ptr++;

		}
	}
}

void	glue_str(char *start, char *end)
{
	size_t i;

	i = 0;
	while (i < ft_strlen(SPACES))
	{
		ft_strrep_range(start, end, SPACES[i], GLUE[i]);
		i++;
	}

}

void	unglue_str(char *start, char *end)
{
	size_t i;

	i = 0;
	while (i < ft_strlen(SPACES))
	{
		ft_strrep_range(start, end, GLUE[i], SPACES[i]);
		i++;
	}
}


/* void	ft_get_strinterval() */
