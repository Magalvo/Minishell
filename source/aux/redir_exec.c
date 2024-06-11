#include "../../include/minishell.h"

void	exec_redir(t_ms *s, t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->file, cmd->mode, 0644);
	if (fd < 0)
		error_msg("err_opening file");
	dup2(fd, cmd->fd);
	close(fd);
	if (cmd->cmd->type == EXEC)
		single_exec(s, cmd->cmd, STDIN_FILENO);
	else if (cmd->cmd->type == PIPE)
		exec_redir(s, cmd->cmd);
	else if (cmd->cmd->type == REDIR)
		exec_pipe(s, cmd->cmd);
}