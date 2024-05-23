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
// ! included in libft
// # include <stdio.h>
// # include <stdlib.h>
// # include <unistd.h>
// ? all structs and defines are here now
# include "minishell_define.h"

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

void	init_env(t_ms *ms, char **envp);
//int	echo_cmd(t_cmd *cmd);
int		env_cmd(t_ms *s);
int		cd_cmd(t_ms *mini);
int		pwd_cmd(t_ms *mini);
int		export_cmd(t_ms *s, char **cmd);
//int	unset_cmd(t_ms *s, t_cmd *cmd);
int		exit_cmd(t_ms *mini);
t_env	*new_env_node(char *env_var);


//*=================== INIT =======================*//


//*==================== AUX =======================*//
void	split_input(t_ms *s, char* input);

/*
ll_inits.c
*/
// void	set_env(s, ep);
// void	set_path(s);
void	init_paths(t_ms *s, char **ep);



//int		ft_exec_buitltins(t_ms *mini, t_cmd *cmds);

//*================= EXEC =========================*//

//todo int		cmd_exec(char *args);

//*================= ERRORS =========================*//

void	error_msg(char *str);

#endif

//! Temporary //

int		exec_input(t_ms *s);
int		ft_exec_buitltins_chr(t_ms *s, char **cmds);
int		echo_cmd_test(char **cmd);
//int		export_cmd_test(t_ms *s, char **cmds);
//int		unset_cmd_test(t_ms *s, char **cmds);
