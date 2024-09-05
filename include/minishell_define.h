/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_define.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:07:20 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/08/02 10:31:31 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DEFINE_H
# define MINISHELL_DEFINE_H

# define STR_SIZE 16
# define MAX_PIDS 1024
# define MIN_PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

# define QUOTE 39
# define DQUOTE 34
# define SPACES		"\t\n\v\f\r "
# define GLUE		"\x01\x02\x03\x04\x05\x06"
# define SYMBOLS	"|&()<>" // { } $ @ ' " \ / * ;
# define TOKENS		"|<>" // { } $ @ ' " \ / * ;
# define UNTOKENS	"\x12\x13\x14" // { } $ @ ' " \ / * ;
# define QUOTES		"'\""
# define UNQUOTES	"\x15\x16"
# define DOLAR		17
# define EMPTY		16
# define EMPTY_STR	"\x10\x00"
// # define EMPTY_ARG 17

//*======================= STRUCTS ====================== *//
typedef struct s_env		t_env;
typedef struct s_ms			t_ms;
typedef struct s_builtin	t_builtin;
typedef struct s_execution	t_execution;		//TODO not defined, still used?
typedef struct s_cmd		t_cmd;
typedef struct s_d_cmd		t_d_cmd;			// two t_cmd pointers
typedef struct s_pids		t_pids;
typedef struct s_sinfo		t_sinfo;
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
	char	*key;
	char	*value;
	t_env	*prev;
	t_env	*next;

};

struct s_ms
{
	char	*prompt;
	char	**paths;
	char	*username;
	int		modal;
	int		infile;
	int		outfile;
	int		exit_stat;
	int		wait;
	char	*input;
	bool	error;
	bool	input_empty;
	bool	bnf;
	char	**env_tmp;
	int		here_doc;
	char	*cmd_temp;
	pid_t	pid;
	bool	tog;
	t_cmd	*ast;
	t_env	*env;
	t_env	*export;
	t_pids	pids_exec;
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
	HEREDOC	= 4,
};

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
	t_cmd	*left;
	t_cmd	*right;
	t_cmd	*cmd;
	pid_t	pid;
	char	*file;
	char	*delim;
	int		mode;
	int		fd;
	char	**temp;
};

struct	s_sinfo
{
	t_cmd	*cmd;
	t_ms	*s;
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
//* MAIN / CHILD / HERE_DOC / IGNORE
//* Redirect Infile
//* Redirect Outfile
//* Exit Status
/*temp for waitpid*/
//* Temp env;
//* NUM of heredocs
//*For here doc signal
//* Command List
//*	ENV Linked List
//* EXPORT List (Sorted)
//* Wiat the cmds
//	int	si_signo; /* signal number */
//	int si_errno; /* if nonzero, errno value from errno.h */
//	int si_code; /* additional info (depends on signal) */
//	pid_t si_pid; /* sending process ID */
//	uid_t si_uid; /* sending process real user ID */
//	void *si_addr; /* address that caused the fault */
//	int si_status; /* exit value or signal number */
//	union sigval si_value; /* application-specific value */
	/* possibly other fields also */
	//*Eg.: PATH=
//*Eg.: /usr/bin (...)
//token
//* 1 -> ENV Originals  2 ->No Value  3 ->Exported with Export
// !======================================
