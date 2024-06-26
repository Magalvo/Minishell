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
	if (!cmds || cmds->type != EXEC)
		return (0);

	if (ft_sw_builtins(cmds->argv[0], "export") == 0)
		return (export_cmd(s, cmds->argv), 1);
	else if (ft_sw_builtins(cmds->argv[0], "cd") == 0)
		return (cd_cmd(s, cmds->argv), 1);
	else
		return (0);
}

int	update_last(t_env *env, char *key, char *value)
{
	char *tmp;
	while (env)
	{
		if (ft_sw_builtins(env->key, key) == 0 && ft_strlen(env->key) == ft_strlen(key))
		{
			if (env->value)
			{
				tmp = env->value;
				env->value = ft_strdup(value);
				free(tmp);
			}
			return (1);
		}
		env = env->next;
	}
	return (0);
}

void	exec_from_ast(t_ms *s)
{
	char *key;

	key = "_";
	if(!exec_paria(s, s->ast))
		exec_from_ast_recursive(s, s->ast, STDIN_FILENO, STDOUT_FILENO);
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
}
