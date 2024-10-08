/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:04:53 by dde-maga          #+#    #+#             */
/*   Updated: 2024/09/19 19:47:50 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

	if (!cmd)
		return (NULL);
	command = check_if_dir(cmd, s);
	if (command == NULL)
		return (NULL);
	command = check_paths(paths, cmd);
	if (command)
		return (command);
	return (get_cmd_from_cwd(cmd));
}

void	new_line(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
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
			dup_and_close(s, &fd_in, &fd_out, STDIN_FILENO);
		if (fd_out != STDOUT_FILENO)
			dup_and_close(s, &fd_out, &fd_in, STDOUT_FILENO);
		if (cmd->error_msg != NULL)
			ft_dprintf(2, "%s\n", cmd->error_msg);
		else if (!cmd->error_msg && \
			!ft_exec_builtins_chr(s, cmd->argv, fd_in, fd_out))
			exec_one(s, cmd->argv);
		clear_fds();
		exit_minishell(s, NULL);
	}
	else
	{
		close_two_fd(cmd, fd_in, fd_out);
		wait_till_end(s, pid, cmd);
	}
}
