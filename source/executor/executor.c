/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:04:53 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/22 16:52:57 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//! exec prototype, (MIGHT GO KABUM!)

static char	*cmd_path(t_ms **paths, t_cmd *cmd)
{
	char	*command;

	if (!paths || !cmd)
		return (NULL);
	while (*paths)
	{
		if (ft_strcmp(*paths, cmd, ft_strlen(*paths)) == 0)
		{
			if (access(cmd, X_OK | F_OK) == 0)
			{
				return (cmd);
			}
			else
			{
				return (NULL);
			}
		}
		command = ft_strjoin(*paths, cmd);
		if (access(command, X_OK | F_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	child_dump(t_ms d)
{
	pipe_msg(d.cmd_args[0]);
	child_free(&d);
	pipe_close(&d);
	free_parent(&d);
	exit(EXIT_FAILURE);
}

static void	ft_dup2(int zero, int first)
{
	dup2(zero, 0);
	dup2(first, 1);
}

void	child(t_ms s, char **argv, t_env *env)
{


	s.pid = fork();
	if (!s.pid)
	{
		if (s.id_n == 0)
			ft_dup2(s.infile, s.pipes[1]);
		else if (s.id_n == s.cmd_nbr - 1)
		{
			ft_dup2(s.pipes[2 * s.id_n - 2], s.outfile);
		}
		else
		{
			ft_dup2(s.pipes[2 * s.id_n - 2], s.pipes[2 * s.id_n + 1]);
		}
		pipe_close(&s);
		s.cmd_args = ft_split(argv[2 + s.here_doc + s.id_n], ' ');
		s.cmd = cmd_path(s.cmd_paths, s.cmd_args[0]);
		if (!s.cmd)
		{
			child_dump(s);
		}
		execve(s.cmd, s.cmd_args, envp);
		child_free(&s);
		error_msg("execve");
	}
}
