
#include "../include/minishell.h"

void	split_input(t_ms *s, char* input)
{
	s.cmd_temp = ft_split(input);
}
