/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_define.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:07:20 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/12 18:14:05 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DEFINE_H
# define MINISHELL_DEFINE_H

# define STR_SIZE 16
# define MAX_PIDS 1024
# define MIN_PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

# define QUOTE '\''
# define DQUOTE '\"'
# define SPACES		"\t\n\v\f\r "
# define GLUE		"\x01\x02\x03\x04\x05\x06"
# define SYMBOLS	"|&()<>" // { } $ @ ' " \ / * ;
# define TOKENS		"|<>" // { } $ @ ' " \ / * ;
# define UNTOKENS	"\x12\x13\x14" // { } $ @ ' " \ / * ;
# define QUOTES		"'\""
# define UNQUOTES	"\x15\x16"
# define DOLAR		'\x11'
# define EMPTY		'\x10'
# define EMPTY_STR	"\x10\0"
// # define EMPTY_ARG 17

//*======================= STRUCTS ====================== *//
typedef struct s_env		t_env;
typedef struct s_ms			t_ms;
typedef struct s_builtin	t_builtin;
typedef struct s_execution	t_execution;		//TODO not defined, still used?
typedef struct s_cmd		t_cmd;
typedef struct s_d_cmd		t_d_cmd;			// two t_cmd pointers
typedef struct s_pids		t_pids;
typedef enum e_signal		t_signal;
typedef enum e_cmd_type		t_cmd_type;
typedef enum e_quote_type	t_quote_type;

struct s_pids
{
	pid_t	pids[MAX_PIDS];
	int		pid_count;
};

struct	s_env
{
	char	*key;	//*Eg.: PATH=
	char	*value;	//*Eg.: /usr/bin (...)
	t_env	*prev;
	t_env	*next;
	//token
	//* 1 -> ENV Originals  2 ->No Value  3 ->Exported with Export
};

struct s_ms
{
	char	*prompt;	//* ARGV
	char	**paths;		//* PATH dir
	char	*username;	//* Current User // ? needed?
	int		modal;		//* MAIN / CHILD / HERE_DOC / IGNORE
	int		infile;		//* Redirect Infile
	int		outfile;	//* Redirect Outfile
	int		exit_stat;	//* Exit Status
	int		wait;		//*temp for waitpid
	char	*input;
	bool	error;
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
	t_pids	pids_exec;	//* Wiat the cmds
};

// ? not used atm
struct s_builtin
{
	char	*name;
	int		(*func)(t_cmd *cmd);
};


enum e_cmd_type
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

struct	s_d_cmd
{
	t_cmd	*one;
	t_cmd	*two;
};

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
	char	**temp;			// ! used?
};

enum e_signal
{
	MAIN,
	CHILD,
	HERE_DOC,
	IGNORE
};

enum e_quote_type
{
	NONE,
	E_QUOTE,
	E_DQUOTE
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
