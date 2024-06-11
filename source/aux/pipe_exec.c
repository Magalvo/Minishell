#include "../../include/minishell.h"


void	exec_one(t_ms *s, char **argv)
{
	char	*path;

	path = cmd_path(s->paths, argv[0]);
	if (!path)
		not_found(argv[0]);
	execve(path, argv, s->env_tmp);																		
	return ;
}

//! ===== Prototype for PIPE execution ======= !//
void	exec_pipe(t_ms *s, t_cmd *cmd)
{
	int		pipefd[2];
	int		fd_in;
	pid_t	pid;

	fd_in = 0;
	while (cmd)
	{
		if(cmd->type == EXEC)
		{
			single_exec(s, cmd, fd_in);
			break;
		}
		else if (cmd->type == PIPE)
		{
			if (pipe(pipefd) == -1)
				error_msg("Urgrrr...piper pipe pipes");
			if ((pid = fork()) == -1)
				error_msg("Ma Fork Broke 3-/-");
			else if(pid == 0)
			{
				dup2(fd_in, 0);
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
				exec_one(s, cmd->left->argv);
			}
			else
			{
				waitpid(pid, NULL, 0);
				close(pipefd[1]);
				fd_in = pipefd[0];
				cmd = cmd->right;
			}
		}
	}
}


void	exec_from_ast(t_ms *s)
{
	t_cmd	*cmd;
	int		fd_in;

	fd_in = 0;
	cmd = s->ast;
	while (cmd)
	{
		if(cmd->type == EXEC)
		{
			single_exec(s, cmd, fd_in);
			break;
		}
		else if(cmd->type == REDIR)
		{
			exec_redir(s, cmd);
			break;
		}
		else if(cmd->type == PIPE)
		{
			exec_pipe(s, cmd);
			break;
		}
		cmd = cmd->right;
	}
}