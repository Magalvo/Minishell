/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:04:53 by dde-maga          #+#    #+#             */
/*   Updated: 2024/07/19 16:21:21 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*aux_cwd(void)
{
	char	*cwd;
	char	*command;

	command = NULL;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		return (NULL);
	}
	command = path_constructor(cwd, command, 1);
	free(cwd);
	if (command && access(command, X_OK | F_OK) == 0)
	{
		return (command);
	}
	free(command);
	return (NULL);
}


char	*cmd_path(char **paths, char *cmd, t_ms *s)
{
	char	*command;
	char	*cwd;

	if (!cmd)
		return (NULL);
	if ((is_dir(cmd) && cmd[0] == '.' && cmd[1] && cmd[1] != '.' \
		&& cmd[1] != '\0') || cmd[0] == '/') //((cmd[0] == '.' && cmd[1]) || cmd[0] == '/')
	{
		ft_dprintf(2, "minishell: %s : Is a directory\n", cmd);
		return (set_exit(126, s), NULL);
	}
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
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		return (NULL);
	}
	command = path_constructor(cwd, cmd, 1);
	free(cwd);
	if (command && access(command, X_OK | F_OK) == 0)
	{
		return (command);
	}
	free(command);
	return (NULL);
}

void	new_line(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
}

static void	assist_file(int fd, int standard)
{
	if (dup2 (fd, standard) == -1)
	{
		perror("dup2");
		exit (1);
	}
	close_fd(&fd);
}

int	fork1(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_msg("minishell: fork error");
	return (pid);
}

void	single_exec(t_ms *s, t_cmd *cmd, int fd_in, int fd_out)
{
	pid_t	pid;

	check_signal(IGNORE);
	pid = fork1();
	if (pid == 0)
	{
		check_signal(CHILD);
		if (fd_in != STDIN_FILENO)
			assist_file(fd_in, STDIN_FILENO);
		else if (fd_out != STDOUT_FILENO)
			assist_file(fd_out, STDOUT_FILENO);
		if (!ft_exec_builtins_chr(s, cmd->argv, fd_in, fd_out))
			exec_one(s, cmd->argv);
		//s->exit_stat = 127;
		exit_minishell(s, NULL);
	}
	else
	{
		if (fd_in != STDIN_FILENO)
			close_fd(&fd_in);
		if (fd_out != STDOUT_FILENO)
			close_fd(&fd_out);
		wait_till_end(s, pid, cmd);
	}
}
