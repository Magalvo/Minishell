/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:04:53 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/22 17:43:04 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//! exec prototype, (MIGHT GO KABUM!)

char	*cmd_path(char **paths, char *cmd)
{
	char	*command;

	if (!paths || !cmd)
		return (NULL);
	if(chdir(cmd) != -1)
	{
		printf("minishell: %s: is a directory\n", cmd);
		exit(EXIT_FAILURE);
	}
	if(cmd[0] == '$')
		exit(EXIT_FAILURE);
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

void	single_exec(t_ms *s, t_cmd *cmd, int fd_in, int fd_out)
{
	pid_t	pid;
	int		status;

	check_signal(IGNORE);
	if((pid = fork()) == -1)
		error_msg("fork");
	else if (pid == 0)
	{
		check_signal(CHILD);
		if (fd_in != STDIN_FILENO)
		{
			dup2 (fd_in, STDIN_FILENO);
			close(fd_in);
		}
		if (fd_out != STDOUT_FILENO)
		{
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		exec_one(s, cmd->argv);
		s->exit_stat = 127;
		not_found(cmd->argv[0], s->exit_stat);
	}
	else
	{
		if (fd_in != STDIN_FILENO)
			close (fd_in);
		if (fd_out != STDOUT_FILENO)
			close(fd_out);
		waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            s->exit_stat = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            s->exit_stat = 128 + WTERMSIG(status);
		printf("EXEC-> %d\n", status); 
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
		printf("STATUS->%d\n", s->exit_stat);
	}
}

/* int exec_input(t_ms *s)
{
	char	*path;
	int		id;

	if (s->ast == NULL)
		return (new_line(), 1);
	if (ft_exec_buitltins_chr(s, s->ast->argv))
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
