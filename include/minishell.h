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
// # include <stdio.h>
// # include <stdlib.h>
// # include <unistd.h>



// !struct siginfo_DontUse
//	int	si_signo; /* signal number */
//	int si_errno; /* if nonzero, errno value from errno.h */
//	int si_code; /* additional info (depends on signal) */
//	pid_t si_pid; /* sending process ID */
//	uid_t si_uid; /* sending process real user ID */
//	void *si_addr; /* address that caused the fault */
//	int si_status; /* exit value or signal number */
//	union sigval si_value; /* application-specific value */
	/* possibly other fields also */
// !======================================


//*======================= STRUCTS ====================== *//
typedef	enum	s_signal t_signal;
typedef struct	s_ms t_ms;
typedef struct	s_builtin t_builtin;

enum s_signal
{
	MAIN,
	CHILD,
	HEREDOC,
	IGNORE
};

struct s_builtin
{
	char	*name;
	int		(*func)(char **args);
};
struct s_ms
{
	char	*prompt;
	int		modal;
};

//*=============== minishell.c =====================*//

int		init_minishell(t_ms *s, char **ep);
// void	exit_minishell(t_ms *s); // changed parameters
void	exit_minishell(t_ms *s, char *msg);
void	minishell(char **envp);
void	check_signal(t_ms *s);
// void	handle_signal(int sign);
void	handler(int signo, siginfo_t *info, void *ptr);

//*================ BUILTINS =====================*//

int		cmd_echo(char **args);
int		cmd_cd(char **args);
int		cmd_pwd(char **args);
int		cmd_export(char **args);
int		cmd_unset(char **args);
int		cmd_env(char **args);
int		cmd_exit(char **args);
int		builtin_num();

//*================= EXEC =========================*//
int		cmd_exec(char **args);

#endif
