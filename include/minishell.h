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
int		cd_cmd(t_ms *mini, char **path);
int		pwd_cmd();
int		export_cmd(t_ms *s, char **cmd);
int		update_key(t_env *env, char *key, char *value);
int		unset_cmd(t_ms *s, char **args);
int		print_export(t_ms *s, int lstsize);
void	exit_cmd(t_ms *s);
char	*get_env_val(t_env *env, char *key);
t_env	*new_env_node(char *env_var);



//*=================== INIT =======================*//


//*=================== PARSE ======================*//
t_cmd	*parse_input(char *input);
char	**create_argv(int argc);


// ! PARSE WIP
t_cmd	*nulterminate(t_cmd *cmd);
int		peek(char **ps, char *es, char *toks);
void	panic(char *s);
int		getcmd(char *buf, int nbuf);
t_cmd	*execcmd(void);
t_cmd	*redircmd(t_cmd *subcmd, char *file, char *efile, int mode, int fd);
t_cmd	*pipecmd(t_cmd *left, t_cmd *right);
int		gettoken(char **ps, char *es, char **q, char **eq);
t_cmd	*parsecmd(char *input);
t_cmd	*parseline(char **ps, char *es);
t_cmd	*parsepipe(char **ps, char *es);
t_cmd	*parseredirs(t_cmd *t_cmd, char **ps, char *es);
t_cmd	*parseexec(char **ps, char *es);



//*==================== AUX =======================*//
void	split_input(t_ms *s, char* input);



/*
ll_inits.c
*/
// void	set_env(s, ep);
// void	set_path(s);


//void	init_paths(t_ms *s, char **ep);



//int		ft_exec_buitltins(t_ms *mini, t_cmd *cmds);

//*================= EXEC =========================*//

//todo int		cmd_exec(char *args);
int				exec_input(t_ms *s);
//char			*search_path(char *command, char **paths);
char			*env_paths(t_ms *ms, char **envp);
int				add_slash(char *slash, char **paths);
char			*cmd_path(char **paths, char *cmd);
//*================= ERRORS =========================*//

void	error_msg(char *str);
int		free_export(char *key, char *value);
void	free_paths(char **paths, int i);

#endif

//! Temporary //

int		exec_input(t_ms *s);
int		ft_exec_buitltins_chr(t_ms *s, char **cmds);
int		echo_cmd_test(char **cmd);
//int		export_cmd_test(t_ms *s, char **cmds);
//int		unset_cmd_test(t_ms *s, char **cmds);
