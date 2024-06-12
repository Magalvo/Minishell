#include "../../include/minishell.h"

void	exec_redir(t_ms *s, t_cmd *cmd)
{
	int		fd;
	pid_t	pid;
	
	fd = open(cmd->file, cmd->mode, 0666);
	if (fd < 0)
		error_msg("err_opening file");
	pid = fork();
	if (pid == -1)
		error_msg("pid");
	else if (pid == 0)
	{
		dup2(fd, cmd->fd);
		close(fd);
		if (cmd->cmd->type == EXEC)
			single_exec(s, cmd->cmd, STDIN_FILENO, STDOUT_FILENO);
		else if (cmd->cmd->type == PIPE)
			exec_pipe(s, cmd->cmd,  STDIN_FILENO, STDOUT_FILENO);
		else if (cmd->cmd->type == REDIR)
			exec_redir(s, cmd->cmd);
		exit(EXIT_SUCCESS);
	}
	else 
	{
		close(fd);
		waitpid(pid, NULL, 0);
	}
}