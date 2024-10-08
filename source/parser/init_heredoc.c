/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:13:04 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/09/20 10:29:27 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*cmd_heredoc(t_cmd *subcmd, char *delim, int mode, t_ms *s)
{
	t_cmd	*cmd;
	char	*filename;
	bool	expand;

	expand = (ft_strchr(delim, '\'') || ft_strchr(delim, '"'));
	cmd = cmd_init(s);
	cmd->type = HEREDOC;
	cmd->cmd = subcmd;
	cmd->mode = mode;
	unglue_str(delim, delim + ft_strlen(delim));
	cmd->delim = reassemble_input(delim);
	str_rm_char(delim, EMPTY);
	filename = ft_getrnd_str();
	cmd->file = ft_strjoin("/tmp/", filename);
	free(filename);
	exit_pack(s, cmd);
	cmd->fd = exec_heredoc(cmd, cmd->file, expand, s);
	if (cmd->fd == -1)
	{
		free_ast(cmd);
		clear_fds();
		return (NULL);
	}
	return (cmd);
}

void	free_herechild(t_cmd **cmd)
{
	int	i;

	i = 0;
	if (*cmd)
	{
		if ((*cmd)->cmd)
		{
			free((*cmd)->cmd->file);
			free((*cmd)->cmd->delim);
			while ((*cmd)->cmd->argv && (*cmd)->cmd->argv[i])
				free((*cmd)->cmd->argv[i++]);
			free((*cmd)->cmd->argv);
			free((*cmd)->cmd);
			(*cmd)->cmd = NULL;
		}
		free((*cmd)->file);
		free((*cmd)->delim);
		i = 0;
		while ((*cmd)->argv && (*cmd)->argv[i])
			free((*cmd)->argv[i++]);
		free((*cmd)->argv);
		free(*cmd);
		*cmd = NULL;
	}
}

int	here_await(pid_t pid, t_ms *s)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		s->exit_stat = WEXITSTATUS(status);
		if (s->exit_stat == 130)
		{
			s->error = true;
			return (-1);
		}
		if (s->exit_stat != 0)
			return (-1);
	}
	return (0);
}

int	exec_heredoc(t_cmd *cmd, char *file, int expand, t_ms *s)
{
	int		fd_file;
	pid_t	pid;
	t_cinfo	cinfo;

	cinfo = cmd_info(NULL, 0);
	fd_file = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_file == -1)
		perror("Error opening here_doc");
	check_signal(IGNORE);
	pid = fork1();
	if (pid == 0)
	{
		s->exit_stat = 0;
		heredoc_child(cmd, fd_file, expand, s);
		free_cmdinfo(&cinfo);
		clear_fds();
		exit_minishell(s, NULL);
	}
	else if (pid > 0)
	{
		close(fd_file);
		if (here_await(pid, s) == -1)
			return (-1);
	}
	return (open_fd(cmd->file, O_RDONLY));
}

void	expand_heredoc(t_ms *s, char *line, int expand, int fd_file)
{
	char	*xp_line;

	if (expand == 0)
	{
		xp_line = expand_here_sw_vars(line, s);
		ft_putendl_fd(xp_line, fd_file);
		free(xp_line);
		xp_line = NULL;
	}
	else
	{
		ft_putendl_fd(line, fd_file);
		free(line);
		line = NULL;
	}
}
