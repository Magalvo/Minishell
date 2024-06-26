
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
	cmd->argv = 0;
	return (cmd);
}

t_cmd *cmd_redir(t_cmd *subcmd, char *filename, int mode, int fd)
{
	t_cmd	*cmd;

	cmd = cmd_init();
	cmd->type = REDIR;
	cmd->cmd = subcmd;
	unglue_str(filename, filename + ft_strlen(filename));
	if (peek_nsp(&filename, filename + ft_strlen(filename), SPACES))
		printf("has spaces: %s", filename);
	cmd->file = filename;
	cmd->mode = mode;
	cmd->fd = fd;
	return (cmd);
}

/*
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
	if (cmd->fd == -1)
	{
		free(cmd->file);
		free(cmd);
		return (NULL);
	}
	check_signal(MAIN);
	return (cmd);
}
*/

/*
void	expand_heredoc(t_ms *s, char *line, int fd_file, char *xp_line)
{
	xp_line = expand_dolar_loop(line, s);
	ft_putstr_fd(xp_line, fd_file);
	ft_putchar_fd('\n', fd_file);
	free(xp_line);
}
*/


/*
int exec_heredoc(char *dli, char *file, int expand, t_ms *s)
{
	int fd;
	int fd_file;
	char *line;
	char *xp_line;
	pid_t frk;
	int status;

	xp_line = NULL;
	fd_file = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_file == -1)
		error_msg("Error opening here_doc");
	check_signal(IGNORE);
	frk = fork();
	if (frk < 0)
	{
		perror("minishell: fork error");
		exit(errno);
	}
	if (frk == 0)
	{
		check_signal(HERE_DOC);
		while (1)
		{
			line = readline("> ");
			if (!line)
				exit(del_eof(fd_file));
			if (ft_strncmp(dli, line, ft_strlen(dli)) == 0)
				break;
			if (expand == 0)
				expand_heredoc(s, line, fd_file, xp_line);
			else
			{
				ft_putstr_fd(line, fd_file);
				free(line);
			}
		}
		free(line);
		close(fd_file);
		exit(0);
	}
	else
	{
		close(fd_file);
		waitpid(frk, &status, 0);
		if (WIFEXITED(status))
		{
			s->exit_stat = WEXITSTATUS(status);
			if(s->exit_stat != 0)
				return(-1);
		}
		fd = open(file, O_RDONLY);
		if (fd < 0)
			error_msg("opening here_doc");
	}
	return (fd);
}
*/

t_cmd *cmd_pipe(t_cmd *left, t_cmd *right)
{
	t_cmd *cmd;

	cmd = cmd_init();
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return (cmd);
}
