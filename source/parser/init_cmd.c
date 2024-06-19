
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

t_cmd *cmd_redir(t_cmd *subcmd, char *filename, int mode, int fd)
{
	t_cmd	*cmd;

	cmd = cmd_init();
	cmd->type = REDIR;
	cmd->cmd = subcmd;
	cmd->file = filename;
	cmd->mode = mode;
	cmd->fd = fd;
	return (cmd);
}

t_cmd *cmd_heredoc(t_cmd *subcmd, char *delim, int mode, t_ms *s)
{
	t_cmd	*cmd;
	char	*filename;

	cmd = cmd_init();
	cmd->type = HEREDOC;
	cmd->cmd = subcmd;
	cmd->mode = mode;
	cmd->delim = delim;
	filename = ft_getrnd_str();
	cmd->file = ft_strjoin("/tmp/", filename);
	free(filename);
	if (!cmd->file)
		perror("strjoin null");
	cmd->fd = exec_heredoc(cmd->delim, cmd->file, \
		(ft_strchr(delim, '\'') || ft_strchr(delim, '"')), s);
	if (!cmd->fd)
		perror("error creating heredoc file");
	return (cmd);
}

int	exec_heredoc(char *dli, char *file, int expand, t_ms *s)
{
	int		fd;
	int		fd_file;
	char	*line;
	char	*xp_line;

	fd_file = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_file == -1)
		error_msg("Error opening here_doc");
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (line == NULL || ft_strncmp(dli, line, ft_strlen(dli)) == 0)
			break ;
		if (expand == 0)
		{
			xp_line = expand_dolar(line, s);
			free(line);
			ft_putstr_fd(xp_line, fd_file);
			free(xp_line);
		}
		else
		{
			ft_putstr_fd(line, fd_file);
			free(line);
		}
	}
	free(line);
	close(fd_file);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_msg("opening here_doc");
	return (fd);
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
