/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:13:04 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/06/27 14:01:07 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	heredoc_child(char *dli, int fd_file, int expand, t_ms *s)
{
	char	*line;
	bool	empty_dli;

	check_signal(HERE_DOC);
	empty_dli = false;
	if (ft_strlen(dli) == 0)
		empty_dli = true;
	while (1)
	{
		line = readline("> ");
		if (!line)
			exit(del_eof(fd_file));
		if ((ft_strncmp(dli, line, ft_strlen(dli)) == 0 && !empty_dli)
			|| (empty_dli && line[0] == '\0'))
			break;
		expand_heredoc(s, line, expand, fd_file);
	}
	free(line);
	close(fd_file);
	exit(0);
}

// void	heredoc_parent(char *dli, int fd_file, int expand, t_ms *s)
// {
// 	close(fd_file);
// 	waitpid(pid, &status, 0);
// 	if (WIFEXITED(status))
// 	{
// 		s->exit_stat = WEXITSTATUS(status);
// 		if(s->exit_stat != 0)
// 			return(-1);
// 	}
// }


int	open_fd(char *file, int mode)
{
	int	fd;

	fd = open(file, mode);
	if (fd < 0)
		error_msg("opening here_doc");
	return (fd);
}

int	del_eof(int heredoc)
{
	close(heredoc);
	ft_putstr_fd("minishell: warning: ", STDOUT_FILENO);
	ft_putstr_fd("here-document ", STDOUT_FILENO);
	ft_putstr_fd("delimited by end-of-file\n", STDOUT_FILENO);
	return (errno);
}
