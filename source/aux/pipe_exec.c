#include "../../include/minishell.h"


void	exec_one(t_ms *s, char **argv)
{
	char	*path;
	char	*cmd_name;

	if ((argv[0][0] == '/' && argv[0][1]) || \
		(argv[0][0] == '.' && argv[0][1] == '/' && argv[0][2]))
    {
        execve(argv[0], argv, s->env_tmp);
		not_found(argv[0], 127, s);
    }
	else
	{
		path = cmd_path(s->paths, argv[0], s);
		if (!path)
			not_found(argv[0], 127, s);
		cmd_name = ft_strchr(path, '/');
		if (cmd_name)
		{
			cmd_name++;
			argv[0] = cmd_name;
		}
		execve(path, argv, s->env_tmp);
		free(path);
		set_exit(126, s);
	}
}

//! ===== Prototype for PIPE execution ======= !//
/* void	exec_pipe(t_ms *s, t_cmd *cmd, int fd_in, int fd_out)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (cmd->type == PIPE)
	{
		if (pipe(pipefd) == -1)
			error_msg("error on pipe");
		if ((pid = fork()) == -1)
			error_msg("error on pid");
		else if (pid == 0)
		{
			close(pipefd[0]);
			dup2(fd_in, STDIN_FILENO);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
			exec_one(s, cmd->left->argv);
			exit(EXIT_SUCCESS);
		}
		else
		{
			close(pipefd[1]);
			wait_till_end(s, pid);
			 waitpid(pid, &status, 0);
			printf("PIPE-> %d\n", status);
			if (WIFEXITED(status))
				s->exit_stat = WEXITSTATUS(status);
			exec_pipe(s, cmd->right, pipefd[0], fd_out);
		}
	}
	else if (cmd->type == REDIR || cmd->type == HEREDOC)
		exec_redir(s, cmd, fd_in, fd_out);
	else
		single_exec(s, cmd, fd_in, fd_out);
} */

int exec_paria(t_ms *s, t_cmd *cmds)
{
	char *key;

	key = ft_strdup("_");
	if (!cmds || cmds->type != EXEC)
		return (0);
	if (ft_sw_builtins(cmds->argv[0], "export") == 0)
	{
		export_cmd(s, cmds->argv);
		export_update(s->export, key, s->ast->argv[s->ast->argc - 1]);
		handle_kv_update(s->env, key, s->ast->argv[s->ast->argc - 1], 1);
		return (1);
	}
 	else if (ft_sw_builtins(cmds->argv[0], "echo") == 0)
	{
		echo_cmd_test(cmds->argv, s);
		export_update(s->export, key, s->ast->argv[s->ast->argc - 1]);
		handle_kv_update(s->env, key, s->ast->argv[s->ast->argc - 1], 1);
		return (1);
	}
	else
		free(key);
	return (0);
}

/* int	update_last(t_env *env, char *key, char *value)
{
	char *tmp;
	while (env)
	{
		if (ft_sw_builtins(env->key, key) == 0 && ft_strcmp(env->key, key) == 0)
		{
			if (env->value && value)
			{
				tmp = env->value;
				free(env->value);
				env->value = tmp;
				env->value = ft_strdup(value);
			}
			return (1);
		}
		env = env->next;
	}
	return (0);
} */
void	updating_cmds(t_ms *s, char *key, char *value)
{
	export_update(s->export, key, value);
	handle_kv_update(s->env, key, value, 1);
}
		
void	exec_from_ast(t_ms *s)
{
/* 	char *key;

	key = ft_strdup("_");
	if (s->ast == NULL)
		return ;
	if (s->ast->type == EXEC && s->ast->argv[s->ast->argc - 1] != NULL)
	{
		update_last(s->env, key, s->ast->argv[s->ast->argc - 1]);
		update_last(s->export, key, s->ast->argv[s->ast->argc - 1]);
	}
	else if (((s->ast->type == REDIR || s->ast->type == HEREDOC) && s->ast->argv[s->ast->argc - 1] != NULL) \
		&& s->ast->argv[s->ast->argc - 1] != NULL)
	{
		update_last(s->env, key, s->ast->cmd->argv[s->ast->cmd->argc - 1]);
		update_last(s->export, key, s->ast->cmd->argv[s->ast->cmd->argc - 1]);
	}
	free(key); */
	if(!exec_paria(s, s->ast))
		exec_from_ast_recursive(s, s->ast, STDIN_FILENO, STDOUT_FILENO);
}
	
	

