#include "../include/minishell.h"
										//s->ast
void exec_from_ast_recursive(t_ms *s, t_cmd *cmd, int fd_in, int fd_out) 
{
	pid_t	pid;
	int		pipefd[2];
	int		fd;
	int		status;

	if (!cmd) 
		return ;
	if (cmd->type == EXEC)
	{
		if(ft_exec_buitltins_chr(s, cmd->argv))
		{
			s->exit_stat = 0;
			return ;
		}
		else
			single_exec(s, cmd, fd_in, fd_out);
	}
	else if (cmd->type == PIPE) 
	{
		if (pipe(pipefd) == -1)
			error_msg("pipe");
		if ((pid = fork()) == -1)
			error_msg("pipe");	
		else if (pid == 0) 
		{
			close(pipefd[0]);
			dup2(fd_in, STDIN_FILENO);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
			exec_from_ast_recursive(s, cmd->left, fd_in, STDOUT_FILENO);
			exit(s->exit_stat);
		} 
		else 
		{
			close(pipefd[1]);
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				s->exit_stat = WEXITSTATUS(status);
			exec_from_ast_recursive(s, cmd->right, pipefd[0], fd_out);
			close(pipefd[0]);
		}
	}
	else if (cmd->type == REDIR) 
	{
		fd = open(cmd->file, cmd->mode, 0644);
		if (fd < 0)
		{
			s->exit_stat = 1;
			return(perror("open"));
		}
		pid = fork();
		if (pid == -1) 
			error_msg("pid");
		else if (pid == 0)
		{
			if (fd_in != STDIN_FILENO) 
			{
				dup2(fd_in, STDIN_FILENO);
				close(fd_in);
			}
			dup2(fd, cmd->fd);
			close(fd);
			exec_from_ast_recursive(s, cmd->cmd, STDIN_FILENO, fd);
			exit(s->exit_stat);
		} 
		else 
		{
			close(fd);
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				s->exit_stat = WEXITSTATUS(status);
		}
	}
}
