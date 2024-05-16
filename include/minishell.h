
#ifndef MINISHELL_H
# define MINISHELL_H
// # include <sys/wait.h>
// # include <sys/stat.h>
# include "../libs/libft/include/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

typedef	enum s_signal
{
	MAIN,
	CHILD,
	HEREDOC,
	IGNORE
} t_signal;


// minishell main struct
typedef struct s_ms
{
	char	*prompt;
	int		modal;
}	t_ms;




//	minishell.c
int			init_minishell(t_ms *s, char **ep);
void		exit_minishell(t_ms *s);
void		minishell(char **envp);
void		check_signal();
static void handle_signal(int sign, t_ms *s);



#endif
