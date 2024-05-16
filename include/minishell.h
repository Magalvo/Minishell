
#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/wait.h>
# include <sys/stat.h>
# include "../libs/libft/include/libft.h"
# include <errno.h>
# include <readline/history.h>
# include <signal.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <dirent.h>


// minishell main struct
typedef	enum s_signal t_signal;
typedef struct s_ms t_ms;

enum s_signal
{
	MAIN,
	CHILD,
	HEREDOC,
	IGNORE
};

struct	s_ms
{
	char	*prompt;
	int		modal;
};




//	minishell.c
int			init_minishell(t_ms *s, char **ep);
void		exit_minishell(t_ms *s);
void		minishell(char **envp);
void		check_signal();
static void handle_signal(int sign, t_ms *s);



#endif
