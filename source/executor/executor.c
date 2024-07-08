/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:04:53 by dde-maga          #+#    #+#             */
/*   Updated: 2024/07/08 17:45:18 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//! exec prototype, (MIGHT GO KABUM!)

char	*cmd_path(char **paths, char *cmd, t_ms *s)
{
	char	*command;

	if (!paths || !cmd)
		return (NULL);
	if (chdir(cmd) == 0 && (cmd[0] == '.' || cmd[0] == '/'))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(" : Is a directory\n", 2);
		return(set_exit(126, s), NULL);
	}
	while (*paths)
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
			return (printf("%s", command), command);
		free(command);
		paths++;
	}
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
		exit(1);
	}
	close(fd);
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
		if (fd_out != STDOUT_FILENO)
			assist_file(fd_out, STDOUT_FILENO);
		exec_one(s, cmd->argv);
		exit_minishell(s, NULL);
	}
	else
	{
		if (fd_in != STDIN_FILENO)
			close (fd_in);
		if (fd_out != STDOUT_FILENO)
			close(fd_out);
		wait_till_end(s, pid, cmd);
	}
}

