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
typedef struct	s_minis t_minis;
typedef struct	s_env t_env;
typedef struct	s_cmd t_cmd;
typedef struct	s_builtin t_builtin;
typedef struct	s_execution t_execution;

enum s_signal
{
	MAIN,
	CHILD,
	HEREDOC,
	IGNORE
};

struct	s_env
{
	char			*key;  //*Eg.: PATH=
	char			*value;//*Eg.: /usr/bin (...)
	int				token; //*Eg.: / | "" ' (...)
	struct s_env	*prev; //* <-
	struct s_env	*next; //* ->
};

struct	s_cmd
{
	char			*env_path;
	char			*cmd;
	char			**cmd_args;
	int				*pipes;
	struct s_cmd	*prev;
	struct s_cmd	*next;

	//todo t_redirs *redir;
	//todo 			executable; 
};

struct s_minis
{
	char	*prompt;
	int		modal;
	t_env	*envlist;
	char	**my_env;
	char	*username;
	int		infile;
	int		outfile;
};

//*=============== minishell.c =====================*//

int		init_minishell(t_minis *s, char **ep);
// void	exit_minishell(t_minis *s); // changed parameters
void	exit_minishell(t_minis *s, char *msg);
void	minishell(char **envp);
void	check_signal(t_minis *s);
// void	handle_signal(int sign);
void	handler(int signo, siginfo_t *info, void *ptr);

//*================ BUILTINS =====================*//

int		echo_cmd(t_cmd *cmd);
int		env_cmd(t_cmd *cmd);
//todo
int		cd_cmd(t_cmd *cmd);
int		pwd_cmd(t_cmd *cmd);
int		export_cmd(t_cmd *cmd);
int		unset_cmd(t_cmd *cmd);
int		exit_cmd(t_cmd *cmd);

struct s_builtin
{
	char	*name;
	int		(*func)(t_cmd *cmd);
};


//*================= EXEC =========================*//
//todo int		cmd_exec(char *args);

//*================= ERRORS =========================*//
void	error_msg(char *str);
#endif
