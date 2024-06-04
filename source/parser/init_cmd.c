
#include "../include/minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(*cmd), sizeof(*cmd));
	// ft_memset(cmd, 0, sizeof(*cmd));
	return (cmd);
}

t_cmd *execcmd(void)
{
	t_cmd	*cmd;

	cmd = init_cmd();
	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = EXEC;
	return (cmd);
}

t_cmd *redircmd(t_cmd *subcmd, char *file, char *efile, int mode, int fd)
{
	t_cmd *cmd;

	// cmd = malloc(sizeof(*cmd));
	// memset(cmd, 0, sizeof(*cmd));
	cmd = init_cmd();
	cmd->type = REDIR;
	cmd->cmd = subcmd;
	cmd->file = file;
	cmd->efile = efile;
	cmd->mode = mode;
	cmd->fd = fd;
	return (cmd);
}

t_cmd *pipecmd(t_cmd *left, t_cmd *right)
{
	t_cmd *cmd;

	// cmd = malloc(sizeof(*cmd));
	// memset(cmd, 0, sizeof(*cmd));
	cmd = init_cmd();
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return (cmd);
}
