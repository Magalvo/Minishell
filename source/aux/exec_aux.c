/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:42:53 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/09/03 19:03:58 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_dir_path(t_ms *s, char **argv)
{
	if (access(argv[0], F_OK) != 0)
	{
		not_found(argv[0], 127, s);
		s->exit_stat = 127;
		return ;
	}
	if (is_dir(argv[0]))
	{
		not_found(argv[0], 127, s);
	}
	else if (access(argv[0], X_OK) != 0)
	{
		not_found(argv[0], 126, s);
		s->exit_stat = 126;
		return ;
	}
	if (!execve(argv[0], argv, s->env_tmp))
		perror("!EXECVE!");
}

void	exec_command_path(t_ms *s, char **argv)
{
	char	*path;
	char	*cmd_name;

	path = cmd_path(s->paths, argv[0], s);
	if (!path)
	{
		not_found(argv[0], 127, s);
		s->exit_stat = 127;
		return ;
	}
	cmd_name = ft_strchr(argv[0], '/');
	if (cmd_name)
	{
		cmd_name++;
		argv[0] = cmd_name;
	}
	execve(path, argv, s->env_tmp);
	free(path);
	not_found(argv[0], 127, s);
	s->exit_stat = 127;
}

char	*check_if_dir(char *cmd, t_ms *s)
{
	if ((is_dir(cmd) && cmd[0] == '.' && cmd[1] && cmd[1] != '.' \
		&& cmd[1] != '\0') || cmd[0] == '/')
	{
		ft_dprintf(2, "minishell: %s : Is a directory\n", cmd);
		set_exit(126, s);
		return (NULL);
	}
	return (cmd);
}

char	*check_paths(char **paths, char	*cmd)
{
	char	*command;

	while (paths && *paths)
	{
		if (ft_strncmp(*paths, cmd, ft_strlen(*paths)) == 0)
		{
			if (access(cmd, X_OK | F_OK) == 0)
				return (cmd);
			else
				return (NULL);
		}
		command = ft_strjoin(*paths, cmd);
		if (access(command, X_OK | F_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

char	*get_cmd_from_cwd(char *cmd)
{
	char	*cwd;
	char	*command;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	command = path_constructor(cwd, cmd, 1);
	free(cwd);
	if (command && access(command, X_OK | F_OK) == 0)
		return (command);
	free(command);
	return (NULL);
}
