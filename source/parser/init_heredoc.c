
#include "../include/minishell.h"


t_cmd *cmd_heredoc(t_cmd *subcmd, char *delim, int mode, t_ms *s)
{
	t_cmd	*cmd;
	char	*filename;

	cmd = cmd_init();
	cmd->type = HEREDOC;
	cmd->cmd = subcmd;
	cmd->mode = mode;
	unglue_str(delim, delim + ft_strlen(delim));
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

int exec_heredoc(char *dli, char *file, int expand, t_ms *s)
{
	int fd_file;
	pid_t frk;
	int status;
	char *line;

	fd_file = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_file == -1)
		error_msg("Error opening here_doc");
	check_signal(IGNORE);
	frk = fork();
	if (frk < 0)
		error_msg("minishell: fork error");
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
			expand_heredoc(s, line, expand, fd_file);
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
	}
	return(open_fd(file, O_RDONLY));
}

int	open_fd(char *file, int mode)
{
	int	fd;

	fd = open(file, mode);
	if (fd < 0)
		error_msg("opening here_doc");
	return (fd);


}

void	expand_heredoc(t_ms *s, char *line, int expand, int fd_file)
{
	char	*xp_line;

	if (expand == 0)
	{
		xp_line = expand_dolar_loop(line, s);
		ft_putendl_fd(xp_line, fd_file);
		free(xp_line);
	}
	else
	{
		ft_putendl_fd(line, fd_file);
		free(line);
	}
}

int	del_eof(int heredoc)
{
	close(heredoc);
	ft_putstr_fd("minishell: warning: ", STDOUT_FILENO);
	ft_putstr_fd("here-document ", STDOUT_FILENO);
	ft_putstr_fd("delimited by end-of-file\n", STDOUT_FILENO);
	return (errno);
}
