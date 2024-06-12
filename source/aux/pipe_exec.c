#include "../../include/minishell.h"


void	exec_one(t_ms *s, char **argv)
{
	char	*path;
	printf("%s", argv[0]);
	if (!ft_strncmp(argv[0], "./minishell", 11))
		execve(argv[0], argv, s->env_tmp);
	path = cmd_path(s->paths, argv[0]);
	if (!path)
		not_found(argv[0]);
	execve(path, argv, s->env_tmp);																	
	error_msg("Error on EXECVE");
}

//! ===== Prototype for PIPE execution ======= !//
void	exec_pipe(t_ms *s, t_cmd *cmd, int fd_in, int fd_out)
{
	int		pipefd[2];
	pid_t	pid;

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
			waitpid(pid, NULL, 0);
			exec_pipe(s, cmd->right, pipefd[0], fd_out);
		}
	}
	else if (cmd->type == REDIR)
		exec_redir(s, cmd, fd_in, fd_out);
	else
		single_exec(s, cmd, fd_in, fd_out);
}


void	exec_from_ast(t_ms *s)
{
	exec_from_ast_recursive(s, s->ast, STDIN_FILENO, STDOUT_FILENO);
}