#include "../../include/minishell.h"

void exec_redir(t_ms *s, t_cmd *cmd, int fd_in, int fd_out)
{
	pid_t	pid;
	int		status;

	if (cmd->type == HEREDOC)
		fd_in = cmd->fd;
	else if ((cmd->mode & O_WRONLY || cmd->mode & O_RDWR)) 
	{
		fd_out = open(cmd->file, cmd->mode, 0666);
		if (fd_out < 0) 
		{
			s->exit_stat = 1;
			return(perror("open"));
		}
	}
	else if (cmd->file) 
	{
		fd_in = open(cmd->file, O_RDONLY);
		if (fd_in < 0) 
		{
			s->exit_stat = 1;
			return(perror("open"));
		}
	}
	pid = fork();
	if (pid == -1)
		error_msg("fork");
	else if (pid == 0) 
	{
		if (fd_in != STDIN_FILENO) 
		{
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		if (fd_out != STDOUT_FILENO) 
		{
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		if (cmd->cmd->type == EXEC) 
			single_exec(s, cmd->cmd, STDIN_FILENO, STDOUT_FILENO);
		else if (cmd->cmd->type == PIPE) 
			exec_pipe(s, cmd->cmd, STDIN_FILENO, fd_out);
	 	else if (cmd->cmd->type == REDIR)
			exec_redir(s, cmd->cmd, STDIN_FILENO, fd_out);
		else if (cmd->cmd->type == HEREDOC)
			exec_redir(s, cmd->cmd, STDIN_FILENO, fd_out);
		exit(s->exit_stat);
	} 
	else 
	{
		if (fd_in != STDIN_FILENO && cmd->file)
			close(fd_in);
		if (fd_out != STDOUT_FILENO)
			close(fd_out);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			s->exit_stat = WEXITSTATUS(status);
	}
}


