/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:04:53 by dde-maga          #+#    #+#             */
/*   Updated: 2024/06/26 19:07:09 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//! exec prototype, (MIGHT GO KABUM!)

char	*cmd_path(char **paths, char *cmd, t_ms *s)
{
	char	*command;

	if (!paths || !cmd)
		return (NULL);
	if (chdir(cmd) != -1)
	{
		printf("minishell: %s: is a directory\n", cmd);
		set_exit(126, s);
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
	dup2 (fd, standard);
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
		not_found(cmd->argv[0], 126, s);
	}
	else
	{
		if (fd_in != STDIN_FILENO)
			close (fd_in);
		if (fd_out != STDOUT_FILENO)
			close(fd_out);
		wait_till_end(s, pid);
	}
}

/* int exec_input(t_ms *s)
{
	char	*path;
	int		id;

	if (s->ast == NULL)
		return (new_line(), 1);
	if (ft_exec_builtins_chr(s, s->ast->argv))
		return (1);
	else
	{
		if(s->ast->type == EXEC)
			exec_one(s, s->ast->argv);
		else if(s->ast->type == PIPE)
			exec_pipe(s, s->ast);
		else if(s->ast->type == REDIR);
		{

		}
	}
	return (1);
} */

/* char *search_path(char *command, char **paths)
{
	char *full_path;
	char *temp_path;
	int i;

	if (!paths)
		return NULL;
	i = 0;
	while (paths[i]) {
		full_path = ft_strjoin(paths[i], "/");
		temp_path = full_path;
		full_path = ft_strjoin(full_path, command);
		free(temp_path);  								//! Free the intermediate string
		if (access(full_path, X_OK) == 0)
			return full_path;  							//!Found executable path
		free(full_path);  								//! Free if not executable
		i++;
	}
	return NULL;
} */

/* void	child_dump(t_ms d)
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
} */

//!!FONTE
/* 		s->exit_stat = status;
		if (status == 131)
			printf("Quit\n");
		if (status == 2)
		{
			s->exit_stat = 130;
			printf("\n");
		}
		if (status > 255)
			status /= 256; */
