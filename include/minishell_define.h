#ifndef MINISHELL_DEFINE_H
# define MINISHELL_DEFINE_H

# define STR_SIZE 16

//*======================= STRUCTS ====================== *//
typedef	enum	s_signal e_signal;
typedef struct	s_env t_env;
typedef struct	s_ms t_ms;
typedef struct	s_builtin t_builtin;
typedef struct	s_execution t_execution;		//TODO not defined, still used?

/* parser structs */
typedef	enum	s_cmd_type e_cmd_type;
typedef	enum	s_quote_type e_quote_type;
typedef	struct	s_cmd t_cmd;
// typedef	struct	s_pid t_pid;

enum s_signal
{
	MAIN,
	CHILD,
	HERE_DOC,
	IGNORE
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
	int		exit_stat;	//* Exit Status
	bool	input_empty;
	bool	bnf;
	char	**env_tmp;	//* Temp env;
	int		here_doc;	//* NUM of heredocs
	char	**cmd_temp;
	pid_t	pid;
	bool	tog;		//*For here doc signal
	t_cmd	*ast;		//* Command List
	t_env	*env;		//*	ENV Linked List
	t_env	*export;	//* EXPORT List (Sorted)
};

// ? not used atm
struct s_builtin
{
	char	*name;
	int		(*func)(t_cmd *cmd);
};

enum s_quote_type
{
	NONE,
	EQUOTE,
	EDQUOTE
};

#define QUOTE '\''
#define DQUOTE '\"'

// struct s_pid
// {
// 	char *env_arg[6];
// };

/*	structs for AST starts here */
# define SPACES		"\t\n\v\f\r "
# define GLUE		"\1\2\3\4\5\6"
# define SYMBOLS	"|&()<>" // { } $ @ ' " \ / * ;
// # define RDONLY		O_RDONLY
// # define TRUNC		O_WRONLY|O_CREAT|O_TRUNC
// # define CREATE		O_WRONLY|O_CREAT
// # define APPEND		O_WRONLY|O_CREAT|O_APPEND

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
	int		type;
	int		argc;
	char	**argv;
	t_cmd	*left;			//pipe
	t_cmd	*right;
	t_cmd	*cmd;			//redir
	pid_t	pid;
	char	*file;
	char	*delim;
	int		mode;
	int		fd;
	char	**temp;
	// char	*argv[MAXARGS];
	// char	*eargv[MAXARGS];
	// char	*efile;
};

//* Integer codes para o tipo de node na ASTree
//* Minuto 4:30 (https://youtu.be/ubt-UjcQUYg?si=ASMMiMFCAmSs3qzx)

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
