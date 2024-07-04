/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:13:04 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/06/29 15:14:53 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


t_cmd *cmd_heredoc(t_cmd *subcmd, char *delim, int mode, t_ms *s)
{
	t_cmd	*cmd;
	char	*filename;
	bool	expand;

	expand = (ft_strchr(delim, '\'') || ft_strchr(delim, '"'));
	cmd = cmd_init();
	cmd->type = HEREDOC;
	cmd->cmd = subcmd;
	cmd->mode = mode;
	unglue_str(delim, delim + ft_strlen(delim));
	ft_strrep_range(delim, NULL, (char)17, '$');
	retokenizer(delim, delim + ft_strlen(delim));
	cmd->delim = remove_quotes(delim, delim);
	filename = ft_getrnd_str();
	cmd->file = ft_strjoin("/tmp/", filename);
	free(filename);
	if (!cmd->file)
		perror("strjoin null");
	// cmd->fd = exec_heredoc(cmd->delim, cmd->file,
		// (ft_strchr(delim, '\'') || ft_strchr(delim, '"')), s);
	cmd->fd = exec_heredoc(cmd->delim, cmd->file, expand, s);
	if (cmd->fd == -1)
	{
		// free(cmd->file);
		// free(cmd);
		return (free(cmd->file), free(cmd), NULL);
	}
	check_signal(MAIN);
	return (cmd);
}

int exec_heredoc(char *dli, char *file, int expand, t_ms *s)
{
	int fd_file;
	pid_t pid;
	int status;
	// char *line;

	fd_file = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_file == -1)
		error_msg("Error opening here_doc");
	check_signal(IGNORE);
	pid = fork1();

	if (pid == 0)
	{
		heredoc_child(dli, fd_file, expand, s);
		// check_signal(HERE_DOC);
		// while (1)
		// {
		// 	line = readline("> ");
		// 	if (!line)
		// 		exit(del_eof(fd_file));
		// 	if (ft_strncmp(dli, line, ft_strlen(dli)) == 0)
		// 		break;
		// 	expand_heredoc(s, line, expand, fd_file);
		// }
		// free(line);
		// close(fd_file);
		// exit(0);
	}
	else
	{
		close(fd_file);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			s->exit_stat = WEXITSTATUS(status);
			if(s->exit_stat != 0)
				return(-1);
		}
	}
	return(open_fd(file, O_RDONLY));
// ! 24 lines without comments, del if ok
}

void	expand_heredoc(t_ms *s, char *line, int expand, int fd_file)
{
	char	*xp_line;

	if (expand == 0)
	{
		xp_line = expand_sw_vars(line, s);
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
