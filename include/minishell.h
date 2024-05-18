#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/include/libft.h"
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <errno.h>
# include <signal.h>
# include <termios.h>
# include <dirent.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef	enum s_signal t_signal;
typedef struct s_ms t_ms;

enum s_signal
{
	MAIN,
	CHILD,
	HEREDOC,
	IGNORE
};

// minishell main struct
struct s_ms
{
	char	*prompt;
	int		modal;
};

// minishell.c
int		init_minishell(t_ms *s, char **ep);
void	exit_minishell(t_ms *s);
void	minishell(char **envp);
void	check_signal(t_ms *s);
void	handle_signal(int sign);

#endif
