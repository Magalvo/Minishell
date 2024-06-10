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
# include "minishell_msgs.h"

//*=============== minishell.c =====================*//

int		init_minishell(t_ms *s, char **ep);
void	exit_minishell(t_ms *s, char *msg);
void	minishell(char **envp);
//void	exit_minishell(t_ms *s); // changed parameters
//void	handle_signal(int sign);

/*
signals.c
*/
//void	check_signal(t_ms *s);
void	check_signal(e_signal sig);
void	handler(int signo, siginfo_t *info, void *ptr);
void	new_line(void);

//*================ BUILTINS =====================*//

void	init_env(t_ms *ms, char **envp);
//int	echo_cmd(t_cmd *cmd);
int		env_cmd(t_ms *s, char **cmds);
int		cd_cmd(t_ms *mini, char **path);
int		pwd_cmd();
int		export_cmd(t_ms *s, char **cmd);
int		update_key(t_env *env, char *key, char *value);
int		unset_cmd(t_ms *s, char **args);
int		print_export(t_env *export);
void	exit_cmd(t_ms *s);
char	*get_env_val(t_env *env, char *key);
t_env	*new_env_node(char *env_var);
void	sort_env_list(t_env **head);
int		print_export(t_env *env);
int		ft_sw_builtins(const char *s1, const char *s2);
int		is_valid_key(const char *key);
char	*get_key_from_str(const char *str);
char	*get_value_from_str(const char *str);
int		handle_kv_update(t_env *env, char *key, char *value);
int		export_update(t_env *export, char *key, char *value);
char	*extract_key(const char *str, char *delimiter);
int		add_new_node(t_env *env, char *key, char *value);
void	init_export(t_ms *ms, char **envp);
int		add_slash(char *slash, char **paths);



//*=================== INIT =======================*//


//*=================== PARSE ======================*//
t_cmd	*parse_input(char *input);
char	**create_argv(int argc);
int		count_argc(char **ps, char *es);
void	ft_strrep_range(char *start, char *end, char search, char replace);
void	glue_str(char *start, char *end);
void	unglue_str(char *start, char *end);

// ! PARSE WIP
// t_cmd	*nulterminate(t_cmd *cmd);
int		peek(char **ps, char *es, char *toks);
void	reprompt(char *s);
int		getcmd(char *buf, int nbuf);
t_cmd	*cmd_init(void);
t_cmd	*cmd_exec(void);
t_cmd	*cmd_redir(t_cmd *subcmd, char *file, char *efile, int mode, int fd);
t_cmd	*cmd_pipe(t_cmd *left, t_cmd *right);
int		get_token(char **ps, char *es, char **q, char **eq);
t_cmd	*parse_cmd(char *input);
t_cmd	*parse_line(char **ps, char *es);
t_cmd	*parse_pipe(char **ps, char *es);
t_cmd	*parse_redir(t_cmd *t_cmd, char **ps, char *es);
t_cmd	*parse_block(char **ps, char *es);
t_cmd	*parse_exec(char **ps, char *es);


//*==================== AUX =======================*//
void	print_ast(t_ms *s, t_cmd *ptr, int padding);
void	print_2d(char **ptr, int padding);


//*==================== AUX =======================*//
void	split_input(t_ms *s, char* input);
char	*get_env_expand(char *key);
void	env_arr_update(t_ms *s);
void	initialize_env(char ***envp);
char	**null_env_init();


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
char			*cmd_path(char **paths, char *cmd);
//*================= ERRORS =========================*//

void	error_msg(char *str);
int		free_export(char *key, char *value);
void	free_paths(char **paths, int i);
int		free_export_p(t_env *env_copy, t_env *new_node);
int		not_found(char *str);


#endif

//! Temporary //

int		exec_input(t_ms *s);
int		ft_exec_buitltins_chr(t_ms *s, char **cmds);
int		echo_cmd_test(char **cmd, t_ms *s);
//int		export_cmd_test(t_ms *s, char **cmds);
//int		unset_cmd_test(t_ms *s, char **cmds);
