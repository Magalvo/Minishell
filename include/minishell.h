/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:07:20 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/09/19 12:17:57 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
// ? all structs and defines are here now
# include "minishell_define.h"
# include "minishell_msgs.h"

//*=============== minishell.c =====================*//

void	minishell(char **envp);
void	exit_minishell(t_ms *s, char *msg);
void	reset_ms(t_ms *s, char *input, int error);
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
void	free2(char *one, char *two);
void	close_fd(int *fd);
void	close_fd_child(t_cmd *cmd, int fd_in, int fd_out);

//*================ BUILTINS =====================*//

void	handle_key(t_ms *s, char *str, char *key);
void	exit_cmd(t_ms *s, char **cmds);
void	sort_env_list(t_env **head);
void	free_key(char **key);
void	unset_aux(t_ms *s, t_env **tmp, char *arg);
void	unset_cmd_aux(t_ms *s, t_env *current);
void	unset_clean(t_env *current);
void	unset_move(t_env *current);
char	*get_key_from_str(const char *str);
char	*get_value_from_str(char *str);
char	*extract_key(const char *str, char *delimiter);
char	*get_env_val(t_env *env, char *key, t_ms *s);
int		env_cmd(t_ms *s, char **cmds);
int		cd_cmd(t_ms *mini, char **path);
int		pwd_cmd(t_ms *s);
int		export_cmd(t_ms *s, char **str);
int		ft_exec_paria(t_ms *s, t_cmd *cmds);
int		is_valid_unset(char	*arg);
int		handle_kv_update(t_env *env, char *key, char *value, int tog);
int		export_update(t_env *export, char *key, char *value);
int		add_new_node(t_env *env, char *key, char *value);
int		add_slash(char *slash, char **paths);
int		print_export(t_env *env);
int		ft_sw_builtins(const char *s1, const char *s2);
int		is_valid_key(char *key);
int		export_unset_error(t_ms *s, char *msg, char *key);
int		export_unset_error(t_ms *s, char *msg, char *key);
int		update_key(t_env *env, char *key, char *value);
int		unset_cmd(t_ms *s, char **args);
int		print_exp(t_env *export);
t_env	*new_env_node(char *env_var);

//*=================== INIT =======================*//

void	init_t_ms(t_ms *s);
void	init_list(t_env **list, char **envp);
void	initialize_env(char ***envp);
void	init_aux(t_env **head, t_env **tail, t_env *new_node);
char	**null_env_init(void);
int		init_minishell(t_ms *s, char **ep);
t_cmd	*cmd_init(t_ms *s);

//*=================== PARSE ======================*//

void	parse_fake_redir(char **ps, char *es, t_ms *s);
void	ft_strrep_range(char *start, char *end, char search, char replace);
void	glue_str(char *start, char *end);
void	unglue_str(char *start, char *end);
void	untokenizer(char *start, char *end);
void	retokenizer(char *start, char *end);
void	unquoter(char *start, char *end);
void	requoter(char *start, char *end);
void	get_endstr_ptr(char **str);
void	skip_spaces(char *str, char *es);
void	get_shrinked(char *input, char *move);
void	str_rm_char(char *input, char remove);
void	expand_heredoc(t_ms *s, char *line, int expand, int fd_file);
void	heredoc_child(t_cmd *cmd, int fd_file, int expand, t_ms *s);
void	reprompt(char *str, int exit_stat, t_ms *s);
void	parse_args(char **ps, char *es, t_d_cmd *cmds, t_ms *s);
char	**create_dptr(int argc);
char	*expand_sw_vars(char *input, t_ms *s);
char	*expand_sw_tilde(char *input, t_ms *s);
char	*expand_sw_quotes(char *input);
char	*get_first_quote(char *input);
char	*vars_sw(char *input, char *ps, t_ms *s);
char	*expand_curly(char *input, char *ps, t_ms *s);
char	*expand_pid(char *input, char *ps, t_ms *s);
char	*expand_exit_stat(char *input, char *ps, t_ms *s);
char	*reassemble_input(char *start);
char	*expand_last_cmd(char *input, char *ps, t_ms *s);
char	*expand_self(char *input, char *ps, t_ms *s);
char	*expand_dolar(char *input, char *ps, t_ms *s);
char	*expand_tilde_equal(char *input, char *ps, t_ms *s);
char	*expand_tilde_pwd(char *input, char *ps, bool check, t_ms *s);
char	*expand_tilde_oldpwd(char *input, char *ps, bool check, t_ms *s);
char	*expand_tilde(char *input, char *ps, bool check, t_ms *s);
char	*remove_quotes(char *input, char *pos);
char	*get_expanded(char *input, char *cut, char *paste, char *remain);
int		count_argc(char **ps, char *es, t_ms *s);
int		is_quoted(const char *str, const char *totest);
int		exec_heredoc(t_cmd *cmd, char *file, int expand, t_ms *s);
int		del_eof(int heredoc);
int		open_fd(char *file, int mode);
int		*magic_key(void);
int		peek(char **ps, char *es, char *toks);
int		peek_nsp(const char *ps, char *es, char *toks);
int		get_token(char **ps, char *es, char **q, char **eq);
int		get_token_a(char **ps);
bool	syntax_validation(char *input, t_ms *s);
bool	syntax_quotes(const char *str);
bool	syntax_pipes(const char *str, const char *end);
bool	syntax_and_or(const char *str);
bool	syntax_list(const char *str);
bool	syntax_back(const char *str);
bool	syntax_parenthesis(const char *str);
bool	syntax_redir(char *str, char *end);
bool	strrchr_alpha_loop(const char *input, const char *pos);
t_cmd	*parse_input(char **input, t_ms *s);
t_cmd	*cmd_exec(t_ms *s);
t_cmd	*cmd_redir_in(t_cmd *subcmd, char *filename, int mode, t_ms *s);
t_cmd	*cmd_redir_out(t_cmd *subcmd, char *filename, int mode, t_ms *s);
t_cmd	*cmd_heredoc(t_cmd *subcmd, char *delim, int mode, t_ms *s);
t_cmd	*cmd_pipe(t_cmd *left, t_cmd *right, t_ms *s);
t_cmd	*parse_cmd(char *input, t_ms *s);
t_cmd	*parse_pipe(char **ps, char *es, t_ms *s);
t_cmd	*parse_redir(t_cmd *t_cmd, char **ps, char *es, t_ms *s);
t_cmd	*redir_sw(t_cmd *cmd, int tok, char *filename, t_ms *s);
t_cmd	*parse_exec(char **ps, char *es, t_ms *s);

//*==================== AUX =======================*//

void	clear_fds(void);
void	print_ast(t_ms *s, t_cmd *ptr, int padding);
void	print_ast_exec(t_ms *s, t_cmd *ptr, int padding);
void	print_ast_pipe(t_ms *s, t_cmd *ptr, int padding);
void	exit_and_found(char *str, int status, t_ms *s);
void	exit_doc(t_ms *s, int heredoc, t_cmd *cmd);
void	free_herechild(t_cmd **cmd);
void	print_ast_redir(t_ms *s, t_cmd *ptr, int padding);
void	print_ast_heredoc(t_ms *s, t_cmd *ptr, int padding);
void	print_exit(t_ms *s, char *cmds, char *str, int status);
void	swipper_fds(void);
void	old_pwd(t_env *env);
void	print_2d(char **ptr, int padding);
char	**create_env_array(int ctd_ptr);
char	*path_constructor(const char *path, const char *cmd, int slashi);
int		is_dir(const char *cmd);
int		cd_cmd_arg_check(t_ms *mini);
int		cd_cmd_handle_home(t_env *env, char **path);
int		cd_cmd_handle_minus(t_env *env, char **path);
int		cd_cmd_change_dir(t_ms *mini, char *dir);
int		cd_cmd_error(char *msg);
int		change_pwd(t_env *env, t_ms *s);
int		cd_cmd_home(t_env *env);
int		cd_cmd_minus(t_env *env);
int		isvar(int c);

//*==================== AUX =======================*//

void	env_arr_update(t_ms *s, char *str);
void	free_and_error(char *one, char *two, char **three);
void	free_env_list(t_env *list);
void	cleanup_shell(t_ms *s);
void	clear_cmd(t_cmd *cmd);
void	free_env_array(char **env_array);
char	*get_env_expand(char *key);
char	**env_convert(t_env *env);
char	**create_env_array(int ctd_ptr);
char	*ft_getrnd_str(void);
char	*ft_get_empty(void);
char	*ft_getpid(void);

//*==================== AUX 3 =======================*//

void	free_node(t_env *node);
void	dup_and_close(t_ms *s, int *fd_this, int *fd_aux, int standard);
char	*join_key_value(const char *key, const char *value);
char	*key_dup(char *env_var, size_t key_len);
int		setting_value(t_env *node, char *delimiter);
int		fork1(void);
int		ft_strcmp(const char *s1, const char *s2);
int		env_pos(t_env *env, char *value);
int		builtins_parent(t_ms *s, char **cmds, int fd_in, int fd_out);

//*================= EXEC =========================*//

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
void	exec_dir_path(t_ms *s, char **argv);
void	exec_command_path(t_ms *s, char **argv);
char	*env_paths(t_ms *ms, char **envp);
char	*cmd_path(char **paths, char *cmd, t_ms *s);
char	*check_if_dir(char *cmd, t_ms *s);
char	*check_paths(char **paths, char	*cmd);
char	*get_cmd_from_cwd(char *cmd);
void	free_cmdinfo(t_cinfo *cinfo);

//*================= ERRORS =========================*//

void	set_exit(int stat, t_ms *s);
void	wait_till_end(t_ms *s, pid_t pid, t_cmd *cmd);
void	error_msg(char *str);
void	free_paths(char **paths, int i);
void	free_all_paths(char **paths);
void	clear_env(char **env);
int		free_export(char *key, char *value);
int		free_export_p(t_env *env_copy, t_env *new_node);
int		not_found(char *str, int status, t_ms *s);
int		export_cmd_error(t_ms *s, char *msg, char *key);
int		ft_exec_builtins_chr(t_ms *s, char **cmds, int fd_in, int fd_out);
int		echo_cmd_test(char **cmd, t_ms *s, int fd_in, int fd_out);
t_sinfo	exit_pack(t_ms *s, t_cmd *cmd);
t_cinfo	cmd_info(t_cmd *cmd, int clear);

#endif

	//! Temporary //
	// int		exec_input(t_ms *s);
	// int		export_cmd_test(t_ms *s, char **cmds);
	// int		unset_cmd_test(t_ms *s, char **cmds);
	//  char	*get_pid(t_ms *s);
	// void	exit_minishell(t_ms *s); // changed parameters
	// void	handle_signal(int sign);

	/*
	signals.c
	*/
	// void	check_signal(t_ms *s);
	// void	init_env(t_ms *ms, char **envp);
	// int	echo_cmd(t_cmd *cmd);
	// void	handle_key(t_ms *s, char **str, char *key, char *value);
	//  void	init_export(t_ms *ms, char **envp);
	//  int		update_last(t_env *env, char *key, char *value);
	//  char	*expand_var(char *input, t_ms *s);
	//  char	*expand_dolar_loop(char *input, t_ms *s);
	// char	expand_braces(char *input);
	//  char	*expand_words(char *input);
	//  bool	check_valid_position(char *input);
	//  int		here_doc(char *dli, t_ms *s, t_cmd *cmd);
	//  t_cmd	*nulterminate(t_cmd *cmd);
	//  t_cmd	*cmd_redir(t_cmd *subcmd, char *filename, int mode, int fd);
	//  t_cmd	*parse_line(char **ps, char *es, t_ms *s);
	//  t_cmd	*parse_block(char **ps, char *es, t_ms *s);
	//  void	parse_args(char **ps, char *es, t_cmd *cmd, t_cmd *ret);
	//  char	*check_abs_or_rel(const char *cmd, t_ms *s);
	//  int		abs_or_rel_path(const	char *cmd);
	// char	*empty(void);
	//  void	split_input(t_ms *s, char* input);
	// int		exec_input(t_ms *s);
	// char	*search_path(char *command, char **paths);
