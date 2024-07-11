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

void	minishell(char **envp);
void	exit_minishell(t_ms *s, char *msg);
int		init_minishell(t_ms *s, char **ep);
void	init_t_ms(t_ms *s);
void	reset_ms(t_ms *s, char *input, int error);
//void	exit_minishell(t_ms *s); // changed parameters
//void	handle_signal(int sign);

/*
signals.c
*/
//void	check_signal(t_ms *s);
void	handler(int signo, siginfo_t *info, void *ptr);
void	sig_ignore(struct sigaction *sa, int signal);
void	here_handler(int signal, siginfo_t *info, void *context);
void	check_signal(t_signal sig);
void	signal_main(struct sigaction sa);
void	signal_child(struct sigaction sa);
void	signal_heredoc(struct sigaction sa);
void	new_line(void);
void	reset_ast(t_ms *s);
void	free_ast(t_cmd *cmd);
void	free_ast2(t_cmd **cmd);
void	free_argv(t_cmd *cmd);
void	free_argv2(t_cmd **cmd);
void	close_fd(int *fd);

//*================ BUILTINS =====================*//

void	init_list(t_env **list, char **envp);
void	init_env(t_ms *ms, char **envp);
//int	echo_cmd(t_cmd *cmd);
int		env_cmd(t_ms *s, char **cmds);
int		cd_cmd(t_ms *mini, char **path);
int		pwd_cmd(t_ms *s);
int		export_cmd(t_ms *s, char **cmd);
int		update_key(t_env *env, char *key, char *value);
int		unset_cmd(t_ms *s, char **args);
int		print_exp(t_env *export);
void	exit_cmd(t_ms *s, char **cmds);
char	*get_env_val(t_env *env, char *key, t_ms *s);
void	sort_env_list(t_env **head);
int		print_export(t_env *env);
int		ft_sw_builtins(const char *s1, const char *s2);
int		is_valid_key(char *key);
char	*get_key_from_str(const char *str);
char	*get_value_from_str(char *str);
int		handle_kv_update(t_env *env, char *key, char *value, int tog);
int		export_update(t_env *export, char *key, char *value);
char	*extract_key(const char *str, char *delimiter);
int		add_new_node(t_env *env, char *key, char *value);
void	init_export(t_ms *ms, char **envp);
int		add_slash(char *slash, char **paths);
t_env	*new_env_node(char *env_var);
int		update_last(t_env *env, char *key, char *value);
int		ft_exec_paria(t_ms *s, t_cmd *cmds);



//*=================== INIT =======================*//


//*=================== PARSE ======================*//
t_cmd	*parse_input(char *input, t_ms *s);
char	**create_dptr(int argc);
int		count_argc(char **ps, char *es, t_ms *s);
void	parse_fake_redir(char **ps, char *es, t_ms *s);
void	ft_strrep_range(char *start, char *end, char search, char replace);
void	glue_str(char *start, char *end);
void	unglue_str(char *start, char *end);
void	untokenizer(char *start, char *end);
void	retokenizer(char *start, char *end);
void	unquoter(char *start, char *end);
void	requoter(char *start, char *end);

void	skip_spaces(char *str, char *es);
char	*reassemble_input(char *start);
bool	syntax_validation(char *input, t_ms *s);
int		syntax_quotes(const char *str);
int		*magic_key(void);
bool	syntax_pipes(const char *str, const char *end);
bool	syntax_and_or(const char *str);
bool	syntax_list(const char *str);
bool	syntax_back(const char *str);
bool	syntax_parenthesis(const char *str);

char	*expand_sw_vars(char *input, t_ms *s);
char	*expand_var(char *input, t_ms *s);
char	*expand_sw_tilde(char *input, t_ms *s);
char	*expand_sw_quotes(char *input);
char	*get_first_quote(char *input);
char	*vars_sw(char *input, char *ps, t_ms *s);
char	*expand_curly(char *input, char *ps, t_ms *s);
char	*expand_pid(char *input, char *ps, t_ms *s);
char	*expand_exit_stat(char *input, char *ps, t_ms *s);
char	*expand_last_cmd(char *input, char *ps, t_ms *s);
char	*expand_self(char *input, char *ps, t_ms *s);
char	*expand_dolar_loop(char *input, t_ms *s);
char	*expand_dolar(char *input, char *ps, t_ms *s);
char	*expand_tilde_equal(char *input, char *ps, t_ms *s);
char	*expand_tilde_pwd(char *input, char *ps, bool check, t_ms *s);
char	*expand_tilde_oldpwd(char *input, char *ps, bool check, t_ms *s);
char	*expand_tilde(char *input, char *ps, bool check, t_ms *s);

bool	strrchr_alpha_loop(const char *input, const char *pos);
int		is_quoted(const char *str, const char *totest);
char	expand_braces(char *input);
char	*expand_words(char *input);
char	*remove_quotes(char *input, char *pos);
bool	check_valid_position(char *input);
char	*get_expanded(char *input, char *cut, char *paste, char *remain);
void	get_shrinked(char *input, char *move);
// int		here_doc(char *dli, t_ms *s, t_cmd *cmd);
int		exec_heredoc(char *dli, char *file, int expand, t_ms *s);
void	expand_heredoc(t_ms *s, char *line, int expand, int fd_file);
void	heredoc_child(char *dli, int fd_file, int expand, t_ms *s);
int		del_eof(int heredoc);
int		open_fd(char *file, int mode);


// ! PARSE WIP
// t_cmd	*nulterminate(t_cmd *cmd);
void	reprompt(char *str, int exit_stat, t_ms *s);
int		peek(char **ps, char *es, char *toks);
int		peek_nsp(const char *ps, char *es, char *toks);
int		getcmd(char *buf, int nbuf);
int		get_token(char **ps, char *es, char **q, char **eq);
int		get_token_a(char **ps);
t_cmd	*cmd_init(void);
t_cmd	*cmd_exec(void);
// t_cmd	*cmd_redir(t_cmd *subcmd, char *filename, int mode, int fd);
t_cmd	*cmd_redir_in(t_cmd *subcmd, char *filename, int mode, t_ms *s);
t_cmd	*cmd_redir_out(t_cmd *subcmd, char *filename, int mode, t_ms *s);
t_cmd	*cmd_heredoc(t_cmd *subcmd, char *delim, int mode, t_ms *s);
t_cmd	*cmd_pipe(t_cmd *left, t_cmd *right);
t_cmd	*parse_cmd(char *input, t_ms *s);
t_cmd	*parse_pipe(char **ps, char *es, t_ms *s);
t_cmd	*parse_redir(t_cmd *t_cmd, char **ps, char *es, t_ms *s);
t_cmd	*redir_sw(t_cmd *cmd, int tok, char *filename, t_ms *s);
// t_cmd	*parse_line(char **ps, char *es, t_ms *s);
// t_cmd	*parse_block(char **ps, char *es, t_ms *s);
t_cmd	*parse_exec(char **ps, char *es, t_ms *s);
void	parse_args(char **ps, char *es, t_d_cmd *cmds, t_ms *s);
// void	parse_args(char **ps, char *es, t_cmd *cmd, t_cmd *ret);


//*==================== AUX =======================*//
void	print_ast(t_ms *s, t_cmd *ptr, int padding);
void	print_ast_exec(t_ms *s, t_cmd *ptr, int padding);
void	print_ast_pipe(t_ms *s, t_cmd *ptr, int padding);
void	print_ast_redir(t_ms *s, t_cmd *ptr, int padding);
void	print_ast_heredoc(t_ms *s, t_cmd *ptr, int padding);
void	print_2d(char **ptr, int padding);
char	*path_constructor(const char *path, const char *cmd, int slashi);
char	*check_abs_or_rel(const char *cmd, t_ms *s);
int		is_dir(const char *cmd);
int		abs_or_rel_path(const	char *cmd);
void	print_exit(t_ms *s, char *cmds, char *str, int status);
// char	*empty(void);


//*==================== AUX =======================*//
void	split_input(t_ms *s, char* input);
char	*get_env_expand(char *key);
void	env_arr_update(t_ms *s, char *str);
void	initialize_env(char ***envp);
char	**null_env_init(void);
void	free_and_error(char *one, char *two, char **three);
char	**env_convert(t_env *env);
char	**create_env_array(int ctd_ptr);
void	free_env_list(t_env *env);
void 	cleanup_shell(t_ms *s);
void	clear_cmd(t_cmd *cmd);
// char	*get_pid(t_ms *s);
char	*ft_getpid(void);
void	free_env_array(char **env_array);
void	init_aux(t_env **head, t_env **tail, t_env *new_node);
char	*ft_getrnd_str(void);

//*==================== AUX 3 =======================*//

void	free_node(t_env *node);
char	*key_dup(char *env_var, size_t key_len);
int		setting_value(t_env *node, char *delimiter);
void	dup_and_close(t_ms *s, int fd, int standard);
int		fork1(void);
int		ft_strcmp(const char *s1, const char *s2);
int		env_pos(t_env *env, char *value);
char	*join_key_value(const char *key, const char *value);


//*================= EXEC =========================*//

//todo int	cmd_exec(char *args);
//int		exec_input(t_ms *s);
//char	*search_path(char *command, char **paths);
char	*env_paths(t_ms *ms, char **envp);
char	*cmd_path(char **paths, char *cmd, t_ms *s);
void	exec_from_ast(t_ms *s);
void	exec_pipe(t_ms *s, t_cmd *cmd, int fd_in, int fd_out);
void	exec_one(t_ms *s, char **argv);
void	single_exec(t_ms *s, t_cmd *cmd, int fd_in, int fd_out);
void	exec_redir(t_ms *s, t_cmd *cmd, int fd_in, int fd_out);
void	exec_redir_fork(t_ms *s, t_cmd *cmd, int fd_in, int fd_out);
void	exec_from_ast_recursive(t_ms *s, t_cmd *cmd, int fd_in, int fd_out);
void	updating_cmds(t_ms *s, t_cmd *cmd, char *value);
void	aux_rec_exec(t_ms *s, t_cmd *cmd, int fd_in, int fd_out);
void	close_two_fd(t_cmd *cmd, int fd_in, int fd_out);
void	fd_errors(t_ms *s, t_cmd *cmd);
void	fd_unlock(t_cmd *cmd, t_ms *s, int *fd, int rd_only);
void	ft_unlock_close(t_cmd *cmd, t_ms *s, int *fd, int rd_only);


//*================= ERRORS =========================*//

void	error_msg(char *str);
int		free_export(char *key, char *value);
void	free_paths(char **paths, int i);
void	free_all_paths(char **paths);
void	clear_env(char **env);
int		free_export_p(t_env *env_copy, t_env *new_node);
int		not_found(char *str, int status, t_ms *s);
int		export_cmd_error(t_ms *s, char *msg, char *key);


//!! To be sorted//
void	set_exit(int stat, t_ms *s);
void	wait_till_end(t_ms *s, pid_t pid, t_cmd *cmd);

#endif

//! Temporary //

//int		exec_input(t_ms *s);
int		ft_exec_builtins_chr(t_ms *s, char **cmds, int fd_in, int fd_out);
int		echo_cmd_test(char **cmd, t_ms *s, int fd_in, int fd_out);
//int		export_cmd_test(t_ms *s, char **cmds);
//int		unset_cmd_test(t_ms *s, char **cmds);
