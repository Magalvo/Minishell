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
	while (*paths)
	{
		if (ft_strncmp(*paths, cmd, ft_strlen(*paths)) == 0)
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
		{
			printf("%s", command);
			return (command);
		}
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
int exec_input(t_ms *s)
{
	char	*path;
	int		id;

	if (s->ast == NULL)
		return (new_line(), 1);
	if (ft_exec_buitltins_chr(s, s->ast->argv))
		return (1);
	id = fork();											//* Fork a new process for external commands
	if (id < 0)
		return (exit_minishell(s, "error"), 0);
	if (id == 0) 											//* Child process
	{
		if (s->ast->type != EXEC)
			exit(0);
		t_cmd	*cast = s->ast;
		path = cmd_path(s->paths, cast->argv[0]);
		if (!path)
		{
			ft_putstr_fd(cast->argv[0], 2);
			exit(EXIT_FAILURE);
		}
		execve(path, cast->argv, s->env_tmp);
		perror("execve");  									//* If execve returns, an error occurred
		exit(EXIT_FAILURE);
	}
	else 													//* Parent process
		wait(NULL);
	return 1;
}



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
