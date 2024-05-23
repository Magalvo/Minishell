#ifndef MINISHELL_DEFINE_H
# define MINISHELL_DEFINE_H

//* Integer codes para o tipo de node na ASTree
//* Minuto 4:30 (https://youtu.be/ubt-UjcQUYg?si=ASMMiMFCAmSs3qzx)

# define EXEC	1
# define REDIR	2
# define PIPE	3
# define LIST	4
# define BACK	5
// * OR *//
/* typedef enum e_command_type {
    EXEC = 1,
    REDIR = 2,
    PIPE = 3,
    LIST = 4,
    BACK = 5
} t_command_type; */

# define MAXARGS 10

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
	//token			env raiz ou added
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
	char	**paths;   	//* PATH dir
	char	*username;	//* Current User // ? needed?
	int		modal;		//* MAIN / CHILD / HERE_DOC / IGNORE
	int		infile;		//* Redirect Infile
	int		outfile;	//* Redirect Outfile
	char	**env_tmp;	//* Temp env;
	char	**cmd_temp;
	t_cmd	*cmds;		//* Command List
	t_env	*env;		//*	ENV copy (Sorted copy)
};

struct s_builtin
{
	char	*name;
	int		(*func)(t_cmd *cmd);
};


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
