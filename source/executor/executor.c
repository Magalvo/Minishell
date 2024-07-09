/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:04:53 by dde-maga          #+#    #+#             */
/*   Updated: 2024/07/09 00:08:16 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*cmd_path(char **paths, char *cmd, t_ms *s)
{
	char	*command;

	if (!paths || !cmd)
		return (NULL);
	if (chdir(cmd) == 0 && (cmd[0] == '.' || cmd[0] == '/'))
	{
		ft_dprintf(2, "minishell: %s : Is a directory\n", cmd);
		return (set_exit(126, s), NULL);
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

static void	assist_file(int fd, int standard, int *exec)
{
	if (dup2 (fd, standard) == -1)
	{
		perror("dup2");
		*exec=0;
		exit(1);
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
	int		exec;

	exec=1;
	check_signal(IGNORE);
	pid = fork1();
	if (pid == 0)
	{
		check_signal(CHILD);
		if (fd_in != STDIN_FILENO)
			assist_file(fd_in, STDIN_FILENO, &exec);
		else if (fd_out != STDOUT_FILENO)
			assist_file(fd_out, STDOUT_FILENO, &exec);
		if(exec)
			exec_one(s, cmd->argv);
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
