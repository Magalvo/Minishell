/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heredoc_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:13:04 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/09/03 12:41:09 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	heredoc_child(t_cmd *cmd, int fd_file, int expand, t_ms *s)
{
	char	*line;
	bool	empty_dli;

	check_signal(HERE_DOC);
	empty_dli = false;
	printf("DELIM |%s|\n", cmd->delim);
	if (ft_strlen(cmd->delim) == 0)
		empty_dli = true;
	while (1)
	{
		line = readline("> ");
		if (!line)
			exit_doc(s, fd_file, cmd);
		if ((ft_strcmp(cmd->delim, line) == 0 && !empty_dli) || (empty_dli
				&& line[0] == '\0'))
			break ;
		expand_heredoc(s, line, expand, fd_file);
	}
	free(line);
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
	{
		return (perror("error opening file"), 0);
	}
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
