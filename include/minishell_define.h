#ifndef MINISHELL_DEFINE_H
# define MINISHELL_DEFINE_H


//*======================= STRUCTS ====================== *//
typedef	enum	s_signal e_signal;
typedef struct	s_ms t_ms;
typedef struct	s_env t_env;
typedef struct	s_builtin t_builtin;
typedef struct	s_execution t_execution;

/* parser structs */
typedef	enum	s_cmd_type e_cmd_type;
typedef struct	s_cmd t_cmd;
typedef struct	s_exec t_exec;
typedef struct	s_redir t_redir;
typedef struct	s_pipe t_pipe;

enum s_signal
{
	MAIN,
	CHILD,
	// HEREDOC,
	// IGNORE
};

struct	s_env
{
	char			*key;  //*Eg.: PATH=
	char			*value;//*Eg.: /usr/bin (...)
	t_env	*prev;
	t_env	*next;
	//token			//* 1 -> ENV Originals  2 ->No Value  3 ->Exported with Export
};

struct s_ms
{
	char	*prompt;	//* ARGV
	char	**paths;   	//* PATH dir
	char	*username;	//* Current User // ? needed?
	int		modal;		//* MAIN / CHILD / HERE_DOC / IGNORE
	int		infile;		//* Redirect Infile
	int		outfile;	//* Redirect Outfile
	bool	input_empty;
	char	**env_tmp;	//* Temp env;
	char	**cmd_temp;
	t_cmd	*ast;		//* Command List
	t_env	*env;		//*	ENV copy (Sorted copy)
	t_env	*export	;	//* EXPORT List
};

// ? not used atm
struct s_builtin
{
	char	*name;
	int		(*func)(t_cmd *cmd);
};

/*	structs for AST starts here */
# define MAXARGS	10 // ! hmm e se quisermos correr um PUSH_SWAP (500 pelo menos)
# define SPACES		"\t\n\v\f\r "
# define SYMBOLS	"|&()<>" // { } $ @ ' " \ / * ;
# define RDONLY		O_RDONLY
# define TRUNC		O_WRONLY|O_CREAT|O_TRUNC
# define CREATE		O_WRONLY|O_CREAT
# define APPEND		O_WRONLY|O_CREAT|O_APPEND

// Parsed command representation
// #define EXEC	1
// #define REDIR	2
// #define PIPE	3
// #define LIST  4
// #define BACK  5

enum s_cmd_type
{
	EXEC	= 1,
	REDIR	= 2,
	PIPE	= 3,
	HEREDOC	= 4, //maybe
};

// struct s_cmd
// {
// 	int type;
// };

struct	s_cmd
{
	int type;
	char *argv[MAXARGS];
	char *eargv[MAXARGS];
	t_cmd *left;			//pipe
	t_cmd *right;
	t_cmd *cmd;				//redir
	char *file;
	char *efile;
	int mode;
	int fd;
	char **temp;
};

struct s_exec
{
	int type;
	char *argv[MAXARGS];
	char *eargv[MAXARGS];
};

struct s_redir
{
	int type;
	t_cmd *cmd;
	char *file;
	char *efile;
	int mode;
	int fd;
};

struct s_pipe
{
	int type;
	t_cmd *left;
	t_cmd *right;
};



//* Integer codes para o tipo de node na ASTree
//* Minuto 4:30 (https://youtu.be/ubt-UjcQUYg?si=ASMMiMFCAmSs3qzx)

// # define EXEC	1
// # define REDIR	2
// # define PIPE	3
// # define LIST	4
// # define BACK	5
// * OR *//
/* typedef enum e_command_type {
    EXEC = 1,
    REDIR = 2,
    PIPE = 3,
    LIST = 4,
    BACK = 5
} t_command_type; */


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
