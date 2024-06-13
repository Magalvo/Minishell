#include "../../include/minishell.h"

void	exec_redir(t_ms *s, t_cmd *cmd, int fd_in, int fd_out)
{
	pid_t	pid;
	
	(void)fd_out;
	fd_out = open(cmd->file, cmd->mode, 0666);
	if (fd_out < 0)
		error_msg("err_opening file");
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
		dup2(fd_out, cmd->fd);
		close(fd_out);
		if (cmd->cmd->type == EXEC)
			single_exec(s, cmd->cmd, STDIN_FILENO, STDOUT_FILENO);
		else if (cmd->cmd->type == PIPE)
			exec_pipe(s, cmd->cmd,  STDIN_FILENO, fd_out);
		else if (cmd->cmd->type == REDIR)
			exec_redir(s, cmd->cmd, STDIN_FILENO, fd_out);
		exit(EXIT_SUCCESS);
	}
	else 
	{
		close(fd_out);
		waitpid(pid, NULL, 0);
	}
}
