
#include "../include/minishell.h"

t_cmd	*cmd_init(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(*cmd), sizeof(*cmd));
	return (cmd);
}

t_cmd *cmd_exec(void)
{
	t_cmd	*cmd;

	cmd = cmd_init();
	cmd->type = EXEC;
	return (cmd);
}

t_cmd *cmd_redir(t_cmd *subcmd, char *file, char *efile, int mode, int fd)
{
	t_cmd	*cmd;
	char	*filename;

	cmd = cmd_init();
	cmd->type = REDIR;
	cmd->cmd = subcmd;
	filename = ft_calloc((efile - file) + 1, sizeof(char));
	ft_memmove((void *)filename, (void *)file, (efile - file));
	// todo free this memory (filename) b4 freeing the struct
	cmd->file = filename;
	// cmd->efile = efile;
	cmd->mode = mode;
	cmd->fd = fd;
	return (cmd);
}

t_cmd *cmd_heredoc(t_cmd *subcmd, int mode, int fd)
{
	t_cmd	*cmd;
	char	*filename;

	(void)subcmd;
	cmd = cmd_init();
	cmd->type = HEREDOC;
	// cmd->cmd = subcmd;
	// todo free this memory (filename) b4 freeing the struct
	filename = ft_getrnd_str();
	cmd->mode = mode;
	cmd->file = ft_strjoin("/temp/", filename);
	if (!cmd->file)
		perror("strjoin null");
	fd = open(cmd->file, mode);
	if (!fd)
		perror("error creating heredoc file");
	cmd->fd = fd;
	return (cmd);
}

t_cmd *cmd_pipe(t_cmd *left, t_cmd *right)
{
	t_cmd *cmd;

	cmd = cmd_init();
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return (cmd);
}
