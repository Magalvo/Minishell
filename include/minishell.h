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

//* Integer codes para o tipo de node na ASTree
//* Minuto 4:30 (https://youtu.be/ubt-UjcQUYg?si=ASMMiMFCAmSs3qzx)

# define EXEC	1
# define REDIR	2
# define PIPE	3
# define LIST	4
# define BACK	5

//*======================= STRUCTS ====================== *//
typedef	enum	s_signal t_signal;
typedef struct	s_ms t_ms;
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
	struct s_env	*prev;
	struct s_env	*next;
};

struct	s_cmd
{
	char			*env_path;
	// char			*cmd; //cmd_args[0]
	char			**cmd_args;
	int				pipes[2];
	int				token;
	int				(*exec)(t_cmd *cmd, t_ms *vars);
	struct s_cmd	*parent;
	struct s_cmd	*left;
	struct s_cmd	*right;

	//todo t_redirs *redir;
	//todo 			executable;
};

struct s_ms
{
	char	*prompt;	//* ARGV
	char	*username;	//* Current User // ? needed?
	int		modal;		//* MAIN / CHILD / HERE_DOC / IGNORE
	int		infile;		//* Redirect Infile
	int		outfile;	//* Redirect Outfile
	char	**cmd_temp;
	t_cmd	*cmds;		//* Command List
	t_env	*env;		//*	ENV copy (Sorted copy)
	char	**path;   	//* PATH dir
};

struct s_builtin
{
	char	*name;
	int		(*func)(t_cmd *cmd);
};

//*=============== minishell.c =====================*//

int		init_minishell(t_ms *s, char **ep);
void	exit_minishell(t_ms *s, char *msg);
void	minishell(char **envp);
//void	exit_minishell(t_ms *s); // changed parameters
//void	handle_signal(int sign);

/*
signals.c
*/
void	check_signal(t_ms *s);
void	handler(int signo, siginfo_t *info, void *ptr);

//*================ BUILTINS =====================*//

int		echo_cmd(t_cmd *cmd);
int		env_cmd(t_ms *mini);
int		cd_cmd(t_ms *mini);
int		pwd_cmd(t_ms *mini);
int		export_cmd(t_ms *mini);
int		unset_cmd(t_ms *mini);
int		exit_cmd(t_ms *mini);

//*=================== INIT =======================*//


//*==================== AUX =======================*//
void	split_input(t_ms *s, char* input);

/*
ll_inits.c
*/
// void	set_env(s, ep);
// void	set_path(s);
void	init_paths(t_ms *s, char **ep);



int		ft_exec_buitltins(t_ms *mini, t_cmd *cmds);

//*================= EXEC =========================*//

//todo int		cmd_exec(char *args);

//*================= ERRORS =========================*//

void	error_msg(char *str);

#endif

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
