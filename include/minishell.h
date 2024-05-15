
#ifndef MINISHELL_H
# define MINISHELL_H
// # include <sys/wait.h>
// # include <sys/stat.h>
# include "../libs/libft/include/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

// minishell main struct
typedef struct s_ms
{
	char	*prompt;
}	t_ms;


//	minishell.c
int		init_minishell(t_ms *s, int ac, char **av, char **ep);
void	exit_minishell(t_ms *s);


#endif
