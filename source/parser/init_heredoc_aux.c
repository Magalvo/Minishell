/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heredoc_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:13:04 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/09/19 17:34:12 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	heredoc_child(t_cmd *cmd, int fd_file, int expand, t_ms *s)
{
	char	*line;
	bool	empty_dli;

	empty_dli = false;
	if (ft_strlen(cmd->delim) == 0)
		empty_dli = true;
	check_signal(HERE_DOC);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			exit_doc(s, fd_file, cmd);
			break ;
		}
		if ((ft_strcmp(cmd->delim, line) == 0 && !empty_dli) || (empty_dli
				&& line[0] == '\0'))
			break ;
		expand_heredoc(s, line, expand, fd_file);
	}
	free(line);
	free_ast(cmd);
	if (s->cmd_temp)
		free(s->cmd_temp);
}

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

// iterates char *input to find $VAR possible to expand, returns expanded string
char	*expand_here_sw_vars(char *input, t_ms *s)
{
	char	*pos;
	char	*xp_input;

	xp_input = ft_strdup(input);
	pos = ft_strchr(xp_input, '$');
	while (pos)
	{
		pos = ft_strchr(xp_input, '$');
		xp_input = vars_sw(xp_input, pos, s);
		pos = ft_strchr(xp_input, '$');
	}
	free(input);
	return (xp_input);
}
